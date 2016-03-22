#include "rpcclient.h"

#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>

void RPCClient::getProductList()
{
	//doGet();
}





QNetworkReply* RPCClient::doUploadFile(QString url, QMap<QString, QString> data, QMap<QString, QString> files, QString functionName)
{
	QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	QHttpPart paramPart;
	QString httpPacket;

	QMap<QString, QString>::const_iterator itor = data.constBegin();
	while (itor != data.constEnd())
	{
		QString key = itor.key();
		QString val = itor.value();

		paramPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\""));
		paramPart.setBody(val.toUtf8());
		multiPart->append(paramPart);

		itor++;
	}


	// 文件上传
	QMap<QString, QString>::const_iterator itorFile = files.constBegin();
	QString filePath;
	QString key;
	while (itorFile != files.constEnd())
	{
		key = itorFile.key();
		filePath = itorFile.value();

		QFile file(filePath);
		QHttpPart filePart;
		filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\"; filename=\"" + file.fileName() + "\""));

		file.open(QIODevice::ReadOnly);
		filePart.setBody(file.readAll());
		//filePart.setBodyDevice(file);
		//file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

		file.close();

		multiPart->append(filePart);

		itorFile++;
	}

	return doPostMultiPart(url, multiPart, functionName, 0, filePath);
}

QNetworkReply* RPCClient::doPostMultiPart(QString url, QHttpMultiPart *multiPart, QString functionName, int retryCount, QString filePath)
{

	QNetworkRequest req;
	req.setUrl(url);

	QNetworkReply* reply = qnam.post(req, multiPart);

	if (retryCount == 0)
	{
		functionName = functionName.mid(functionName.indexOf("::") + 2);
		functionName = functionName + "Result";
	}

	RequestItem item;
	item.submitUrl = url;
	item.retryCount = retryCount;
	item.functionName = functionName;
	item.multiPart = multiPart;
	item.reqType = 3;
	item.startTime = QTime::currentTime();
	item.filePath = filePath;

	m_requestHash[reply] = item;

	connect(reply, SIGNAL(finished()), SLOT(onFinished()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onError(QNetworkReply::NetworkError)));

	return reply;
}


QNetworkReply* RPCClient::doPost(QString url, QMap<QString, QString> data, QString functionName)
{
	QMap<QString, QString>::const_iterator it = data.constBegin();
	QStringList params;
	while (it != data.constEnd())
	{
		QString key = QUrl::toPercentEncoding(it.key());
		QString val = QUrl::toPercentEncoding(it.value());
		QString param = QString("%1=%2").arg(key).arg(val);
		params.append(param);
		it++;
	}
	QString buf = params.join("&");
	QByteArray content = buf.toUtf8();

	QNetworkReply* reply = doPost(url, content, functionName);
	return reply;
}

QNetworkReply* RPCClient::doPost(QString url, QByteArray content, QString functionName, int retryCount)
{
	int contentLength = content.length();
	QNetworkRequest req;
	req.setUrl(QUrl(url));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	req.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);
	QNetworkReply *reply = qnam.post(req, content);

#ifndef QT_NO_SSL
	connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

	if (retryCount == 0)
	{
		functionName = functionName.mid(functionName.indexOf("::") + 2);
		functionName = functionName + "Result";
	}

	RequestItem item;
	item.submitUrl = url;
	item.retryCount = retryCount;
	item.functionName = functionName;
	item.postData = content;
	item.reqType = 2;
	item.multiPart = 0;
	item.startTime = QTime::currentTime();

	m_requestHash[reply] = item;

	connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));

	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onReceive()));

	return reply;
}

QNetworkReply* RPCClient::doGet(QString url, QString functionName, int retryCount)
{

	QNetworkRequest req;
	req.setUrl(QUrl(url));
	QNetworkReply *reply = qnam.get(req);

#ifndef QT_NO_SSL
	connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

	if (retryCount == 0)
	{
		functionName = functionName.mid(functionName.indexOf("::") + 2);
		functionName = functionName + "Result";
	}

	RequestItem item;
	item.submitUrl = url;
	item.retryCount = retryCount;
	item.functionName = functionName;
	item.reqType = 1;
	item.multiPart = 0;
	item.startTime = QTime::currentTime();

	m_requestHash[reply] = item;

	connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
	return reply;
}

void RPCClient::sslErrors(const QList<QSslError> &sslErrors)
{
#ifndef QT_NO_SSL
	foreach(const QSslError &error, sslErrors)
		fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
	Q_UNUSED(sslErrors);
#endif
}


void RPCClient::onError(QNetworkReply::NetworkError error)
{
	// network layer error error >= QNetworkReply::ConnectionRefusedError && error <= QNetworkReply::UnknownNetworkError && 
	if (error != QNetworkReply::OperationCanceledError)
	{
		QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

		qDebug() << "WebApiManager::onError" << reply->url().toString() << reply->errorString();;
		handleError(reply);
	}

}

void RPCClient::handleError(QNetworkReply* reply)
{
	RequestItem item = m_requestHash[reply];
	m_requestHash.remove(reply);

	int retryCount = item.retryCount;
	if (retryCount >= 2)
	{
		// 重试两次后提示错误


		QString sigal = item.functionName;

		QJsonValue jsonVal = QJsonValue::fromVariant(QString::fromUtf8(item.postData));
		QMetaObject::invokeMethod(this, sigal.toStdString().c_str(), Qt::DirectConnection,
			Q_ARG(int, 999),
			Q_ARG(QJsonValue, jsonVal));

		emit onNetWorkError(sigal);

	}
	else
	{
		retryCount++;
		if (item.reqType == 1)
		{
			doGet(item.submitUrl, item.functionName, retryCount);
		}
		else if (item.reqType == 2)
		{
			doPost(item.submitUrl, item.postData, item.functionName, retryCount);
		}
		else if (item.reqType == 3)
		{
			doPostMultiPart(item.submitUrl, item.multiPart, item.functionName, retryCount, item.filePath);
		}
	}
	//reply->abort();
}

void RPCClient::onFinished()
{
	int code = 0;
	QJsonValue jsonVal;
	bool result = false;

	QByteArray content;
	QNetworkReply *reply = NULL;

	if (reply = qobject_cast<QNetworkReply *>(sender()))
	{
		RequestItem item = m_requestHash[reply];
		m_requestHash.remove(reply);

		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		if (reply->error() != QNetworkReply::NoError)
			//if(statusCode != 200 && statusCode != 302) 
		{
			return;
		}

		if (item.multiPart)
		{
			item.multiPart->setParent(reply); // delete the multiPart with the reply
		}

		content = reply->readAll();

		QJsonDocument doc(QJsonDocument::fromJson(content));
		QJsonObject json = doc.object();

		code = json["code"].toString().toInt();
		jsonVal = json["value"];
		if (code != 0)
		{
			qDebug() << reply->url().toString() << "error code :" << content << ";postdata=" << item.postData;
		}

		if (item.functionName == "uploadCrashReportResult")
		{
			jsonVal = item.filePath;
		}

		QMetaObject::invokeMethod(this, item.functionName.toStdString().c_str(), Qt::DirectConnection,
			Q_ARG(int, code),
			Q_ARG(QJsonValue, jsonVal));
	}


}
#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include <QHttpMultiPart>

#include <QJsonValue>

#include <QTime>

class RPCClient : public QObject
{
	Q_OBJECT

public:
	~RPCClient() { instance = nullptr; }

	static RPCClient* Get()
	{
		if (instance == nullptr)
			instance = new RPCClient;
		return instance;
	}

	struct RequestItem {
		QString submitUrl;
		int reqType; // 1: get 2:post
		QByteArray postData;
		QString functionName;
		QHttpMultiPart* multiPart;
		int retryCount;
		QTime startTime; // ��ʼʱ��
		QString filePath; // �ļ�·��
	};

public:
	void getProductList();

signals:
	void onNetWorkError(QString req);
	void onTimeout(QString req);

private slots:
	void sslErrors(const QList<QSslError> &errors);

	void onError(QNetworkReply::NetworkError error);

	void onFinished();

private:
	// Multipart ��ʽ�ύ����
	QNetworkReply* doUploadFile(QString url, QMap<QString, QString> data, QMap<QString, QString> files, QString functionName);

	QNetworkReply* doPostMultiPart(QString url, QHttpMultiPart *multiPart, QString functionName, int retryCount = 0, QString filePath = "");

	// Post��ʽ����
	QNetworkReply* doPost(QString url, QMap<QString, QString> data, QString functionName);

	QNetworkReply* doPost(QString url, QByteArray data, QString functionName, int retryCount = 0);
	// get��ʽ����
	QNetworkReply* doGet(QString url, QString functionName, int retryCount = 0);


	void handleError(QNetworkReply* reply);

private:
	static RPCClient* instance;

	QNetworkAccessManager qnam;
	QHash<QNetworkReply*, RequestItem> m_requestHash;
	
};

#endif // RPCCLIENT_H

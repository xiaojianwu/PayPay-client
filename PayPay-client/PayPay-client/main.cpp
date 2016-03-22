#include "mainframe.h"
#include <QtWidgets/QApplication>

#include <QFile>

#include <qtranslator.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	//为程序添加翻译文件，解决中文乱码问题
	QTranslator translator;
	QByteArray qmData;

	QString qmPath = QString(":/paypay-client_zh.qm");
	QFile qmFile(qmPath);
	if (qmFile.open(QFile::ReadOnly))
	{
		qmData.append(qmFile.readAll());
		qmFile.close();
		bool ret = translator.load((uchar*)qmData.data(), qmData.length());
	}
	a.installTranslator(&translator);


	QFile qss(":/Resources/css/StyleSheet.css");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();


	MainFrame w;
	w.show();
	return a.exec();
}

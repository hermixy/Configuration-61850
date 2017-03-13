﻿#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "datastruct.h"
#include <QMessageBox>
QTranslator *g_appTranslator;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	//QTextCodec *xcodec = QTextCodec::codecForLocale();
	//QString exeDir = xcodec->toUnicode(QByteArray(argv[0]));
	//QString BKE_CURRENT_DIR = QFileInfo(exeDir).path();
	//qt has a bug in 5.2.1(windows)? so I use setLibraryPaths
	//QApplication::setLibraryPaths(QApplication::libraryPaths() << BKE_CURRENT_DIR);
	g_appTranslator = new QTranslator();
	bool bSucc = g_appTranslator->load("./Configuration_zh.qm");

	if (bSucc == false)
	{
		QMessageBox::warning(NULL, "Warning", ("load Configuration_zh.qm failed."));
	}
	a.installTranslator(g_appTranslator);
	MainWindow w;
	w.show();

	return a.exec();
}

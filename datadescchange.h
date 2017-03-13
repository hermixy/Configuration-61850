﻿#ifndef DATADESCCHANGE_H
#define DATADESCCHANGE_H

#include <QDialog>
#include "ui_datadescchange.h"

class DataDescChange : public QDialog
{
	Q_OBJECT

public:
	DataDescChange(QWidget *parent = 0);
	~DataDescChange();
    QString strDesc1;
    QString strDesc2;
    QString strDU1;
	QString strDU2;
	void Display(QString strDesc1, QString strDesc2, QString strDU1, QString strDU2);
private slots:
    void Pushbutton_Apply();
    void Pushbutton_Cancel();
    void TextChange1(QString text);
    void TextChange2(QString text);
private:
	Ui::DataDescChange ui;
};

#endif // DATADESCCHANGE_H

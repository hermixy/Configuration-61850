﻿#ifndef IMPORTXLS_H
#define IMPORTXLS_H

#include <QDialog>
#include "ui_importxls.h"
#include<QStandardItemModel>
#include"userdefinedelegate.h"
#include"scdtree.h"
#include<QInputDialog>
#include"datastruct.h"
#include<QVector>
#include<QFileDialog>
class ImportXLS : public QDialog
{
	Q_OBJECT

public:
	ImportXLS(QWidget *parent = 0);
	~ImportXLS();
    void Init_dlg();
    void Check_IED();
    QStringList headerList;
	QStandardItemModel   *Model;
    ScdTree *Point;
    QString File;
    QVector<Map_IED> IED_Map;
private slots:
    void Pushbutton_Browse();
    void Pushbutton_Ok();
    void Pushbutton_Cancel();
private:
	Ui::ImportXLS ui;
};

#endif // IMPORTXLS_H
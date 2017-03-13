﻿#ifndef IMPORTXLS_RS_H
#define IMPORTXLS_RS_H

#include <QDialog>
#include "ui_importxls_rs.h"
#include<QMap>
#include"datastruct.h"
#include<QStandardItemModel>

class ImportXLS_RS : public QDialog
{
	Q_OBJECT

public:
	ImportXLS_RS(QWidget *parent = 0);
	~ImportXLS_RS();
    QMap<QString,Input_Mapping>Map_Repeat;
    QMap<QString,Input_Mapping>Map_invalid_IN;
    QMap<QString,Input_Mapping>Map_invalid_OUT;

    QMap<QString,Input_Mapping>Map_available;
    QStringList IEDList;
   // QList<QTableView *> tableViewList;
	QMap<QString, QTableView *> tableViewMap;
    QTableView *tableView;
    QStandardItemModel   *Model;
    //QList<QStandardItemModel *> ModelList;
	QMap<QString, QStandardItemModel *>ModelMap;
    void Init_dlg();
    void Display();
private slots:
    void Pushbutton_Apply();
    void Pushbutton_Cancel();
private:
	Ui::ImportXLS_RS ui;
};

#endif // IMPORTXLS_RS_H

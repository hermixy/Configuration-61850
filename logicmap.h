﻿#ifndef LOGICMAP_H
#define LOGICMAP_H

#include <QDialog>
#include"scdtree.h"
//#include <QSql>
#include <QSqlQuery> 
#include <QFileDialog>
#include <QSqlDatabase>
#include<QMessageBox>
#include <QStandardItemModel>
#include"XML.h"
#include <QTreeWidgetItem>
#include "sqlite3.h"
#include <QTextCodec>
#include <QBitArray>
#include"stationpara.h"
#include"userdefinedelegate.h"
#include<QMap>

namespace Ui {
class LogicMap;
}

class LogicMap : public QDialog
{
    Q_OBJECT

public:
    explicit LogicMap(QWidget *parent = 0);
	QString file_map;
	QString file_db;
    ~LogicMap();
	ScdTree *Point_SCD;
    XML *Point_MAP;
    Model_XML Model_CUR;
	//QSqlQuery m_sql;
	void Init_dlg();
	QStringList headerList;
    QMap<QString ,QString> Dev_Map;
	QVector<Model_Struct> Model_List;
	QVector<DataSetStruct> DataSetList;
	QVector<Device_Type>	DeviceType_List;
    int Init_DB(QString filename);
    void Inittableview_dev(int type);
	void Init_combox_dev();
    QStandardItemModel *m_ModelDEV;
    QStandardItemModel *m_ModelIED;
    QStandardItemModel *m_ModelMAP;
	QItemSelectionModel *m_ModelSlection;

    void DisplayDev(int type);
    void DisplayYX(QVector<YX_Struct>&,QVector<BI_struct>&);
    void DisplayYC(QVector<YC_Struct>&,QVector<AI_struct>&);
    void DisplayKWH(QVector<KWH_Struct>&,QVector<CI_struct>&);
    void DisplayYK(QVector<YK_Struct>&,QVector<BO_struct>&);
	void DisplaySG(QVector<SG_Struct>&, QVector<SG_struct>&);
    void Initcombox_type();
	void Initcombox_IEDtype();
    void Initcombox_ied();
    void Initcombox_LD(QString IEDName);
    void DisplayDataFromLD(QString str);
	void GetDeviceList();

    int Creat_flag;
    //QSqlDatabase DB_FILE;
	sqlite3 *db;
	sqlite3_stmt * stmt;
    bool Save_flag;
	int State_Type;
private slots:
    void radioButton_new_clicked();
    void radioButton_browse_clicked();
    void pushbutton_DB();
    void pushbutton_browse();
    void pushbutton_save();
    void pushbutton_station();
    void pushbutton_apply();
    void comboxe_dev_change(QString index);
    void comboxe_type_change(QString index);
    void comboxe_ied_change(QString index);
    void comboxe_ld_change(QString index);
	void comboxe_Iedtype_change(QString index);
    void receivedragEnterEvent(QDropEvent *event);
    void OnDataChanged(const QModelIndex &, const QModelIndex &);
	void pushbutton_clear();
    void pushbutton_Del();
private:
    Ui::LogicMap *ui;
};

#endif // LOGICMAP_H

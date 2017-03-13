﻿#ifndef MMSEXTRA_H
#define MMSEXTRA_H

#include <QDialog>
#include "datastruct.h"
#include <QStandardItemModel>
#include"scdtree.h"
#include <QVector>
#include"userdefinedelegate.h"
namespace Ui {
class MMSExtra;
}

class MMSExtra : public QDialog
{
    Q_OBJECT

public:
    explicit MMSExtra(QWidget *parent = 0);
    ~MMSExtra();
    QStandardItemModel *ModelIED_MMS;
    QStandardItemModel *ModelIED_GOOE;
    QStandardItemModel *ModelIED_SMV;

	void Init_dlg();
    void Get_Data();
	void Dispplay();
    int CheckIP(QString,int row ,int column);
    //int CheckMac(QString);
    //int CheckVLAN(QString);
    //int CheckSMVID(QString);
    //int CheckGOOSEID(QString);
    QString m_IED;
    QString m_AP;
public:
	ConnectedAP ConnectAP;
    QVector<Address_GOOSE> m_GOOSE;
    QVector<Address_SMV> m_SMV;
    ScdTree *m_Point;
    QStringList headerList;
private slots:
    void OnMMSDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
    void OnGOOSEDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
    void OnSMVDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
	void onpushbutton_apply();
	void onpushbutton_cancel();
private:
    Ui::MMSExtra *ui;
};

#endif // MMSEXTRA_H

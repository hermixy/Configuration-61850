﻿#ifndef LEGITIMACYVERIFICATION_H
#define LEGITIMACYVERIFICATION_H

#include <QDialog>
#include "ui_legitimacyverification.h"
#include "mainwindow.h"
#include"wait_dlg.h"
class LegitimacyVerification : public QDialog
{
	Q_OBJECT

public:
	LegitimacyVerification(QWidget *parent = 0);
	~LegitimacyVerification();
    void Init_dlg();
    int  CheckComm();
    int  CheckFCDA();
    int  CheckMapping();
    int  CheckSender();
    int  CheckReference();
    void  DisCheckComm();
    void  DisCheckFCDA();
    void  DisMapping();
    void  DisCheckSender();
    void  DisCheckReceiver();
    void  DisCheckReference();
    void  DisWarning();
    //void  DisReference();
	ScdTree *m_Point;
    QStringList comm_errList;
    QStringList FCDA_errList;
    QStringList Receiver_errList;
    QStringList Sender_errList;
    QStringList Reference_errList;
    QStringList comm_warnList;
    QStringList FCDA_warnList;
    QStringList Receiver_warnList;
    QStringList Sender_warnList;
    QStringList Reference_warnList;
private slots:
    void Pushbutton_Check_Click();
private:
	Ui::LegitimacyVerification ui;
};

#endif // LEGITIMACYVERIFICATION_H
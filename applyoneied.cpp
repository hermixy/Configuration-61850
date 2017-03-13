﻿#include "applyoneied.h"
#include "ui_applyoneied.h"

ApplyOneIED::ApplyOneIED(QWidget *parent) :
QDialog(parent),
ui(new Ui::ApplyOneIED)
{
	ui->setupUi(this);
	//Init_dlg(0);
	connect(ui->pushButton_Apply, SIGNAL(clicked()), this, SLOT(Pushbutton_apply()));
	connect(ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(Pushbutton_cancel()));

}

ApplyOneIED::~ApplyOneIED()
{
	delete ui;
}
void ApplyOneIED::Init_dlg(int sta)
{
	ui->label_AD1->setText(tr("IP1"));
	ui->label_AD2->setText(tr("IP2"));
	ui->label_AE_Qua->setText(tr("AE_Qualifier"));
	ui->label_Psel->setText(tr("Psel"));
	ui->label_Tsel->setText(tr("TSel"));
	ui->label_Ssel->setText(tr("Ssel"));
	ui->label_AP_Title->setText(tr("AP_Title"));
	ui->label_AuthCode->setText(tr("AuthCode"));
	ui->label_Ctltime->setText(tr("CtlTime"));
	ui->label_GITime->setText(tr("GITime"));
	ui->label_KeepLive->setText(tr("KeepLive"));
	ui->label_LostTime->setText(tr("LostTime"));
	ui->label_name->setText(tr("Name"));
	ui->label_RptBuf->setText(tr("RptBufTime"));
	ui->label_RptInt->setText(tr("RptIntgPd"));
	ui->label_Timeserver->setText(tr("Time Server"));
	ui->label_AuthMod->setText(tr("AuthMod"));
	ui->label_type->setText(tr("IED Type"));
	ui->pushButton_Apply->setText(tr("Apple"));
	ui->pushButton_Cancel->setText(tr("Cancel"));
	ui->label_ChanMod->setText(tr("ChanMod"));
	headerlist.clear();
	headerlist << tr("CLIENT") << tr("SERVER");
	ui->comboBox_time->addItems(headerlist);

	headerlist.clear();
	headerlist << tr("UNPASS") << tr("PASS");
	ui->comboBox_pass->addItems(headerlist);
	headerlist.clear();
	headerlist << tr("HOTBACKUP") << tr("COLDBACKUP");
	ui->comboBox_ChanMod->addItems(headerlist);
	for (int i = 0; i < DeviceType_List.size(); i++)
	{
		ui->comboBox_type->addItem(DeviceType_List[i].Name);
	}
	state = sta;
	if (sta == 1)
	{

		ui->label_AE_Qua->hide();

		ui->label_Psel->hide();
		ui->label_Tsel->hide();
		ui->label_Ssel->hide();
		ui->label_AP_Title->hide();
		ui->label_AuthCode->hide();
		ui->label_Ctltime->hide();
		ui->label_GITime->hide();
		ui->label_KeepLive->hide();
		ui->label_LostTime->hide();
		ui->comboBox_pass->hide();
		ui->label_RptBuf->hide();
		ui->label_RptInt->hide();
		ui->label_Timeserver->hide();
		ui->label_AuthMod->hide();
		ui->comboBox_time->hide();
		ui->comboBox_pass->hide();
		ui->label_ChanMod->hide();
		ui->comboBox_ChanMod->hide();

		ui->lineEdit_AE_Qua->hide();

		ui->lineEdit_AP_Title->hide();
		ui->lineEdit_AuthCode->hide();
		ui->lineEdit_CtlTime->hide();
		ui->lineEdit_GITime->hide();
		ui->lineEdit_KeepLive->hide();
		ui->lineEdit_LostTime->hide();
		ui->lineEdit_Psel->hide();
		ui->lineEdit_RptBuf->hide();
		ui->lineEdit_RptInt->hide();
		ui->lineEdit_Ssel->hide();
		ui->lineEdit_Tsel->hide();

	}

}
void ApplyOneIED::DisplayDevice(int sta)
{
	state = sta;
	if (sta == 2)
	{
		OldName = IED.Name;
	}
	ui->lineEdit_name->insertItem(0,IED.Name);
    int with =ui->comboBox_type->width();
	ui->lineEdit_name->setFixedWidth(with);
    ui->lineEdit_name->addItems(IEDlist);
	ui->lineEdit_AD1->setText(RemoteAddres.Addr1);
	ui->lineEdit_AD2->setText(RemoteAddres.Addr2);
	ui->lineEdit_AE_Qua->setText(RemoteAddres.AE_Qualifier);
	ui->lineEdit_AP_Title->setText(RemoteAddres.Ap_Title);
	ui->lineEdit_AuthCode->setText(IED.AuthCode);
	ui->lineEdit_CtlTime->setText(IED.CtlTimeOut);
	ui->lineEdit_GITime->setText(IED.GITime);
	ui->lineEdit_KeepLive->setText(IED.KeepLive);
	ui->lineEdit_LostTime->setText(IED.LostConTime);
	ui->lineEdit_RptBuf->setText(IED.RptBufTime);
	ui->lineEdit_RptInt->setText(IED.RptIntgPd);
	ui->lineEdit_Ssel->setText(RemoteAddres.Ssel);
	ui->lineEdit_Psel->setText(RemoteAddres.Psel);
	ui->lineEdit_Tsel->setText(RemoteAddres.Tsel);
	ui->comboBox_ChanMod->setCurrentText(IED.ChanMod);
	ui->comboBox_pass->setCurrentText(IED.AuthMod);
	ui->comboBox_time->setCurrentText(IED.TimeServMode);
	ui->comboBox_type->setCurrentText(IED.Type);
}
void ApplyOneIED::CreatOneIED()
{
	IED.Name = "New IED";
	IED.ChanMod = "HOTBACKUP";
	IED.TimeServMode = "CLIENT";
	IED.CtlTimeOut = "3";
	IED.GITime = "3000";
	IED.RptBufTime = "1000";
	IED.RptIntgPd = "3000";
	IED.LostConTime = "5";
	IED.KeepLive = "10";
	IED.AuthMod = "UNPASS";
	IED.AuthCode = "123456";
	RemoteAddres.Name = "New IED";
	RemoteAddres.Addr1 = "192.168.100.1";
	RemoteAddres.Addr2 = "192.168.200.1";
	RemoteAddres.Ap_Title = "1 3 9999 23";
	RemoteAddres.AE_Qualifier = "23";
	RemoteAddres.Psel = "00 00 00 01";
	RemoteAddres.Ssel = "00 01";
	RemoteAddres.Tsel = "00 01";

}
void ApplyOneIED::Pushbutton_apply()
{
	IED.Name = ui->lineEdit_name->currentText();
	IED.Vendor = ui->comboBox_type->currentText();
	for (int i = 0; i < DeviceType_List.size(); i++)
	{
		if (IED.Vendor == DeviceType_List[i].Name)
		{
			IED.Type = DeviceType_List[i].Type;
		}
	}
	IED.ChanMod = ui->comboBox_ChanMod->currentText();
	IED.TimeServMode = ui->comboBox_time->currentText();
	IED.CtlTimeOut = ui->lineEdit_CtlTime->text();
	IED.GITime = ui->lineEdit_GITime->text();
	IED.RptBufTime = ui->lineEdit_RptBuf->text();
	IED.RptIntgPd = ui->lineEdit_RptInt->text();
	IED.LostConTime = ui->lineEdit_LostTime->text();
	IED.KeepLive = ui->lineEdit_KeepLive->text();
	IED.AuthMod = ui->comboBox_pass->currentText();
	IED.AuthCode = ui->lineEdit_AuthCode->text();
	RemoteAddres.Name = ui->lineEdit_name->currentText();
	RemoteAddres.Addr1 = ui->lineEdit_AD1->text();
    int recode;
    recode= Check_IP(RemoteAddres.Addr1);
    if(recode==DO_FAIL)
        return ;
	RemoteAddres.Addr2 = ui->lineEdit_AD2->text();
    recode= Check_IP(RemoteAddres.Addr2);
    if(recode==DO_FAIL)
        return ;
	RemoteAddres.Ap_Title = ui->lineEdit_AP_Title->text();
	RemoteAddres.AE_Qualifier = ui->lineEdit_AE_Qua->text();
	RemoteAddres.Psel = ui->lineEdit_Psel->text();
	RemoteAddres.Ssel = ui->lineEdit_Ssel->text();
	RemoteAddres.Tsel = ui->lineEdit_Tsel->text();
	//RemoteAddres.NetType = ui->comboBox_type->currentText();
	int ret;
	if (state != 2)
	{
		ret = Point->CheckName(IED.Name);
		if (ret == DO_OK)
		{
			QMessageBox msgBox;
			msgBox.setText("The IED Name is exist");
			msgBox.setInformativeText("Check the name and reset");
			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			msgBox.setDefaultButton(QMessageBox::Yes);
			int ret = msgBox.exec();
			if (ret == QMessageBox::No)
			{
				return;
			}
		}
		else{
			accept();
		}
	}
	else
	{
         accept();


	}


}
void ApplyOneIED::Pushbutton_cancel()
{
	reject();
}
int ApplyOneIED::Check_IP(QString sIP)
{
    if ((sIP.isEmpty()))
    {
        return DO_FAIL;
    }

    if (sIP.count(".") != 3)
    {
        QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
        return DO_FAIL;
    }

    QStringList listNum = sIP.split(".", QString::SkipEmptyParts);
    qint8 bCount = listNum.count();

    if (bCount != 4)
    {
        QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
        return DO_FAIL;
    }
    bool bret;
    for (int i = 0; i < bCount; i++)
    {

        int iNum;
        iNum = listNum[i].toInt(&bret);

        if (!bret)
        {
            QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
            return DO_FAIL;
        }
        if (i == 0)
        {
            if (iNum == 0)
            {
                QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
                return DO_FAIL;
            }

        }
        if ((iNum > 255))
        {
            QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
            return DO_FAIL;
        }
    }
    if ((listNum[0].toInt(&bret) == 0) && (listNum[1].toInt(&bret) == 0)&&(listNum[2].toInt(&bret) == 0)&&(listNum[3].toInt(&bret) == 0))
    {
        QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
        return DO_FAIL;
    }
    if ((listNum[0].toInt(&bret) == 127) && (listNum[1].toInt(&bret) == 0) && (listNum[2].toInt(&bret) == 0) && (listNum[3].toInt(&bret) == 1))
    {
        QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
        return DO_FAIL;
    }
    return DO_OK;
}

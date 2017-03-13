﻿#include "mmsextra.h"
#include "ui_mmsextra.h"

MMSExtra::MMSExtra(QWidget *parent) :
QDialog(parent),
ui(new Ui::MMSExtra)
{
	ui->setupUi(this);
	//QRegExp mac_reg_exp("^([0-9A-F]{2})(-[0-9A-F]{2}){5}$");
	//QRegExpValidator *validator_mac = new QRegExpValidator(mac_reg_exp, this);
	//QRegExp reg_exp_Vlan("^[0-9A-F]{3}$");
	//QRegExp reg_exp_Appid("^[0-9A-F]{4}$");
	//QRegExpValidator *validator_VLAN = new QRegExpValidator(reg_exp_Vlan);
	//QRegExpValidator *validator_APPID = new QRegExpValidator(reg_exp_Appid);
	ModelIED_MMS = new QStandardItemModel;
	ModelIED_GOOE = new QStandardItemModel;
	ModelIED_SMV = new QStandardItemModel;
	m_Point = NULL;
	Init_dlg();
	connect(ui->pushButton_Apply, SIGNAL(clicked()), this, SLOT(onpushbutton_apply()));
	connect(ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onpushbutton_cancel()));
}

MMSExtra::~MMSExtra()
{
	delete ui;


}
void MMSExtra::Init_dlg()
{
	disconnect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
	disconnect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
	disconnect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));

	headerList.clear();
	headerList << tr("IEDname") << tr("Access Point") << tr("IP") << tr("OSI-AP-Title") << tr("OSI-AE-Qualifier") << tr("OSI-PSEL") << tr("OSI-SSEL")
		<< tr("OSI-TSEL");
	ui->tableView_MMS->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView_MMS->setSelectionMode(QAbstractItemView::SingleSelection);
	ModelIED_MMS->clear();
	ModelIED_MMS->setColumnCount(headerList.count());
	ui->tableView_MMS->setModel(ModelIED_MMS);
	for (int i = 0; i < headerList.count(); i++)
	{
		ModelIED_MMS->setHeaderData(i, Qt::Horizontal, headerList.at(i));
		ui->tableView_MMS->setItemDelegateForColumn(i, ui->tableView_MMS->itemDelegateForColumn(0));
	}
	IPEditer *IP_editor = new IPEditer(this);
	ui->tableView_MMS->setItemDelegateForColumn(2, IP_editor);
	headerList.clear();
	headerList << tr("IEDname") << tr("Access Point") << tr("cbName") << tr("LdInst") << tr("MAC-Address") << tr("APPID")
		<< tr("VLAN-ID") << tr("VLAN-PRIORITY") << tr("MinTime") << tr("MaxTime");


	ui->tableView_GOOSE->setSelectionBehavior(QAbstractItemView::SelectItems);
	ui->tableView_GOOSE->setSelectionMode(QAbstractItemView::ExtendedSelection);

	ModelIED_GOOE->clear();
	ModelIED_GOOE->setColumnCount(headerList.count());
	ui->tableView_GOOSE->setModel(ModelIED_GOOE);
	for (int i = 0; i < headerList.count(); i++)
	{
		ModelIED_GOOE->setHeaderData(i, Qt::Horizontal, headerList.at(i));
		ui->tableView_GOOSE->setItemDelegateForColumn(i, ui->tableView_GOOSE->itemDelegateForColumn(0));
	}
	//MACEditer *Mac_editor = new MACEditer(this);
	//ui->tableView_GOOSE->setItemDelegateForColumn(4, Mac_editor);
    APPIDEditer *Appid_editor = new APPIDEditer(this);
    ui->tableView_GOOSE->setItemDelegateForColumn(5, Appid_editor);
    VLANEditer *Vlan_editor = new VLANEditer(this);
    ui->tableView_GOOSE->setItemDelegateForColumn(6, Vlan_editor);
	headerList.clear();
	headerList << tr("IEDname") << tr("Access Point") << tr("cbName") << tr("LdInst") << tr("MAC-Address") << tr("APPID")
		<< tr("VLAN-ID") << tr("VLAN-PRIORITY");


	ui->tableView_SMV->setSelectionBehavior(QAbstractItemView::SelectItems);
	ui->tableView_SMV->setSelectionMode(QAbstractItemView::ExtendedSelection);

	ModelIED_SMV->clear();


	ModelIED_SMV->setColumnCount(headerList.count());

	ui->tableView_SMV->setModel(ModelIED_SMV);
	for (int i = 0; i < headerList.count(); i++)
	{
		ModelIED_SMV->setHeaderData(i, Qt::Horizontal, headerList.at(i));
		ui->tableView_SMV->setItemDelegateForColumn(i, ui->tableView_SMV->itemDelegateForColumn(0));
	}
	//ui->tableView_SMV->setItemDelegateForColumn(4, Mac_editor);
    ui->tableView_SMV->setItemDelegateForColumn(5, Appid_editor);
    ui->tableView_SMV->setItemDelegateForColumn(6, Vlan_editor);
	connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
	connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
	connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));

	//ui->label_ied->setText(tr("IEDName"));
	//ui->label_AE->setText(tr("AE-Qualifier"));
	//ui->label_ap->setText(tr("AccessPoint"));
	//ui->label_APPIDG->setText(tr("Appid"));
	//ui->label_APPIDS->setText(tr("Appid"));
	//ui->label_IP->setText(tr("IP"));
	//ui->label_MACG->setText(tr("Mac Addr"));
	//ui->label_MACS->setText(tr("Mac Addr"));
	//ui->label_MAXG->setText(tr("Max Time"));
	//ui->label_MAXS->setText(tr("Max Time"));
	//ui->label_MING->setText(tr("Min Time"));
	//ui->label_MINS->setText(tr("Min Time"));
	//ui->label_PSEL->setText(tr("PSEL"));
	//ui->label_SSEL->setText(tr("SSEL"));
	//ui->label_Title->setText(tr("AP-Title"));
	//ui->label_TSEL->setText(tr("TSEL"));
	//ui->label_VLAN_IDG->setText(tr("VLAN ID"));
	//ui->label_VLAN_IDS->setText(tr("VLAN ID"));
	//ui->label_VLAN_PRIG->setText(tr("VLAN PRIORITY"));
	//ui->label_VLAN_PRIS->setText(tr("VLAN PRIORITY"));
	//ui->label_cbs->setText(tr("cbName"));
	//ui->label_cbg->setText(tr("cbName"));
	//ui->label_lds->setText(tr("ldInst"));
	//ui->label_ldg->setText(tr("ldInst"));
	//ui->lineEdit_cbg->setEnabled(false);
	//ui->lineEdit_cbs->setEnabled(false);
	//ui->lineEdit_lds->setEnabled(false);
	//ui->lineEdit_ldg->setEnabled(false);
	ui->pushButton_Apply->setText(tr("Apply"));
	ui->pushButton_Cancel->setText(tr("Cancel"));
	//ui->tabBox_mms->setTabText(0, tr("MMS"));
	//ui->tabBox_mms->setTabText(1, tr("GOOSE"));
	//ui->tabBox_mms->setTabText(2, tr("SMV"));
	//ui->tabBox_mms->setCurrentIndex(0);
}
void MMSExtra::Get_Data()
{
	m_GOOSE.clear();
	m_SMV.clear();
	m_Point->GetConnectAPData(m_IED, m_AP, ConnectAP, m_GOOSE, m_SMV);
}

void MMSExtra::Dispplay()
{
	disconnect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
	disconnect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
	disconnect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));

	ModelIED_MMS->setRowCount(1);
	ModelIED_MMS->setData(ModelIED_MMS->index(0, 0), ConnectAP.iedName);
	ModelIED_MMS->item(0, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	ModelIED_MMS->setData(ModelIED_MMS->index(0, 1), ConnectAP.apName);
	ModelIED_MMS->item(0, 1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	ModelIED_MMS->setData(ModelIED_MMS->index(0, 3), ConnectAP.iP_addr.s_AP_Title);
	ModelIED_MMS->setData(ModelIED_MMS->index(0, 4), ConnectAP.iP_addr.s_AE_Qualifier);
	ModelIED_MMS->setData(ModelIED_MMS->index(0, 5), ConnectAP.iP_addr.s_PSEL);
	ModelIED_MMS->setData(ModelIED_MMS->index(0, 6), ConnectAP.iP_addr.s_SSEL);
	ModelIED_MMS->setData(ModelIED_MMS->index(0, 7), ConnectAP.iP_addr.s_TSEL);
	ModelIED_MMS->setData(ModelIED_MMS->index(0, 2), ConnectAP.iP_addr.s_IP);
	ModelIED_GOOE->setRowCount(m_GOOSE.size());
	for (int i = 0; i < m_GOOSE.size(); i++)
	{
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 0), ConnectAP.iedName);
		ModelIED_GOOE->item(i, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 1), ConnectAP.apName);
		ModelIED_GOOE->item(i, 1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 2), m_GOOSE.at(i).s_cbName);
		ModelIED_GOOE->item(i, 2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 3), m_GOOSE.at(i).s_ldInst);
		ModelIED_GOOE->item(i, 3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 4), m_GOOSE.at(i).s_MAC_addr);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 5), m_GOOSE.at(i).s_APPID);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 6), m_GOOSE.at(i).s_VLAN_ID);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 7), m_GOOSE.at(i).s_VLAN_PRIORITY);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 8), m_GOOSE.at(i).s_MinTime);
		ModelIED_GOOE->setData(ModelIED_GOOE->index(i, 9), m_GOOSE.at(i).s_MaxTime);
	}
	ModelIED_SMV->setRowCount(m_SMV.size());
	for (int i = 0; i < m_SMV.size(); i++)
	{
		ModelIED_SMV->setData(ModelIED_SMV->index(i, 0), ConnectAP.iedName);
		ModelIED_SMV->item(i, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		ModelIED_SMV->setData(ModelIED_SMV->index(i, 1), ConnectAP.apName);
		ModelIED_SMV->item(i, 1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ModelIED_SMV->setData(ModelIED_SMV->index(i, 2), m_SMV.at(i).s_cbName);
		ModelIED_SMV->item(i, 2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ModelIED_SMV->setData(ModelIED_SMV->index(i, 3), m_SMV.at(i).s_ldInst);
		ModelIED_SMV->item(i, 3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ModelIED_SMV->setData(ModelIED_SMV->index(i, 4), m_SMV.at(i).s_MAC_addr);
		ModelIED_SMV->setData(ModelIED_SMV->index(i, 5), m_SMV.at(i).s_APPID);
		ModelIED_SMV->setData(ModelIED_SMV->index(i, 6), m_SMV.at(i).s_VLAN_ID);
		ModelIED_SMV->setData(ModelIED_SMV->index(i, 7), m_SMV.at(i).s_VLAN_PRIORITY);
	}
    ui->tabWidget->setCurrentIndex(0);
	connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
	connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
	connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));

}
void MMSExtra::OnMMSDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    int row = topLeft.row();
    int column = topLeft.column();
    disconnect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
    if(column==2)
    {
        QString str = ModelIED_MMS->data(ModelIED_MMS->index(row,column)).toString();
       CheckIP(str,row,column);
	}
	else if (column==3)
	{
		QString str = ModelIED_MMS->data(ModelIED_MMS->index(row, column)).toString();
		for (int i = 0; i < str.length(); i++)
		{
			QChar chr;
			chr = str.at(i);
			if (i==0)
			{
				if (chr == ',')
				{
					QMessageBox::about(0, tr("Error"), tr("Wrong AP-Title\nIt should likes 1 3 9999 33 or 1,3,9999,33"));
					ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_AP_Title);
					connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
					return;
				}
			}
			if (!chr.isNumber())
			{
				if (!chr.isSpace())
				{
					if (chr != ',')
					{
						QMessageBox::about(0, tr("Error"), tr("Wrong AP-Title\nIt should likes 1 3 9999 33 or 1,3,9999,33"));
						ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_AP_Title);
						connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
						return;
					}
				}
			}
		}
	}
	else 	if (column == 4)
	{
		QString str = ModelIED_MMS->data(ModelIED_MMS->index(row, column)).toString();

		for (int i = 0; i < str.length(); i++)
		{
			QChar chr;
			chr = str.at(i);
			if (!chr.isNumber())
			{
				QMessageBox::about(0, tr("Error"), tr("Wrong AP-Qualifier\n It should be likes 33"));
				ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_AE_Qualifier);
				connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
				return;
			}
		}

	}
	else 	if (column == 5)
	{
		QString str = ModelIED_MMS->data(ModelIED_MMS->index(row, column)).toString();

		for (int i = 0; i < str.length(); i++)
		{
			QChar chr;
			chr = str.at(i);
			if (!chr.isNumber())
			{
				if (!chr.isSpace())
				{

					QMessageBox::about(0, tr("Error"), tr("Wrong OSI-PSEL\nIt should  likes 00 00 00 01"));
					ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_PSEL);
					connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
					return;
				}
			}
		}
	}
	else 	if (topLeft.column() == 6)
	{
		QString str = ModelIED_MMS->data(ModelIED_MMS->index(row, column)).toString();

		for (int i = 0; i < str.length(); i++)
		{
			QChar chr;
			chr = str.at(i);
			if (!chr.isNumber())
			{
				if (!chr.isSpace())
				{

					QMessageBox::about(0, tr("Error"), tr("Wrong OSI-SSEL\nIt should  likes  00 01"));
					ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_SSEL);
					connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
					return;

				}
			}
		}
	}
	if (column == 7)
	{
		QString str = ModelIED_MMS->data(ModelIED_MMS->index(row, column)).toString();

		for (int i = 0; i <str.length(); i++)
		{
			QChar chr;
			chr = str.at(i);
			if (!chr.isNumber())
			{
				if (!chr.isSpace())
				{

					QMessageBox::about(0, tr("Error"), tr("Wrong OSI-TSEL\nIt should  likes  00 01"));
					ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_TSEL);
					connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));
					return;
					
				}
			}
		}
	}
   // {
   //     QString str = ModelIED_MMS->data(ModelIED_MMS->index(row,column)).toString();
   //     for(int i =0;i<str.length();i++)
   //     {
   //         QChar chr = str.at(i);
			//if (!chr.isNumber() && !chr.isSpace())
   //         {
   //             QMessageBox::about(0, tr("Error"), tr("Only can input number or space"));
   //          if(column==3)
   //          {
   //              ModelIED_MMS->setData(ModelIED_MMS->index(0, 3), ConnectAP.iP_addr.s_AP_Title);
   //          }
   //          if(column==4)
   //          {
   //              ModelIED_MMS->setData(ModelIED_MMS->index(0, 4), ConnectAP.iP_addr.s_AE_Qualifier);

   //          }
   //          if(column==5)
   //          {
   //              ModelIED_MMS->setData(ModelIED_MMS->index(0, 5), ConnectAP.iP_addr.s_PSEL);

   //          }
   //          if(column==6)
   //          {
   //              ModelIED_MMS->setData(ModelIED_MMS->index(0, 6), ConnectAP.iP_addr.s_SSEL);

   //          }
   //          if(column==7)
   //          {
   //              ModelIED_MMS->setData(ModelIED_MMS->index(0, 7), ConnectAP.iP_addr.s_TSEL);

   //          }
			// break;
   //         }
   //     }
   // }
    connect(ModelIED_MMS, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnMMSDataChanged(const QModelIndex &, const QModelIndex &)));

}

void MMSExtra::OnGOOSEDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    int row = topLeft.row();
    int column = topLeft.column();
	QString str;
	bool ok;
    disconnect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
	//ModelIED_GOOE->setData(ModelIED_GOOE->index(row, 4), m_GOOSE.at(row).s_MAC_addr);
	//ModelIED_GOOE->setData(ModelIED_GOOE->index(row, 7), m_GOOSE.at(row).s_VLAN_PRIORITY);

	//ModelIED_GOOE->setData(ModelIED_GOOE->index(row, 5), m_GOOSE.at(row).s_APPID);

	//ModelIED_GOOE->setData(ModelIED_GOOE->index(row, 6), m_GOOSE.at(row).s_VLAN_ID);
	str = ModelIED_GOOE->data(ModelIED_GOOE->index(row, column)).toString();
	if (column == 4)
	{
		if ((str.isEmpty()))
		{
			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), m_GOOSE.at(row).s_MAC_addr);
			connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}

		if (str.count("-") != 5)
		{
			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), m_GOOSE.at(row).s_MAC_addr);
			connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}
		QStringList listNum = str.split("-", QString::SkipEmptyParts);
		qint8 bCount = listNum.count();

		if (bCount != 6)
		{
			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), m_GOOSE.at(row).s_MAC_addr);
			connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}

		for (int i = 0; i < bCount; i++)
		{
			bool bret;
			int iNum;
			iNum = listNum[i].toInt(&bret, 16);

			if (!bret)
			{
				QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
				ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), m_GOOSE.at(row).s_MAC_addr);
				connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
				return;
			}

			if ((iNum > 0xFF))
			{
				QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
				ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), m_GOOSE.at(row).s_MAC_addr);
				connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
				return;
			}
		}
		if (listNum.at(5).length()<2)
		{
			listNum[5] = "0" + listNum[5];
			str.clear();
			str = listNum.at(0);
			for (int m = 1; m < listNum.size(); m++)
			{
				str += "-" + listNum.at(m);
			}
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), str);
			connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}

	}
	else if (column==5)
	{

		if ((0x3FFF < str.toUInt(&ok, 16)) || (0x0000 > str.toUInt(&ok, 16)))
		{
			QMessageBox::about(0, tr("Error"), tr("APPID of GOOSE must be between 0000-3FFF"));
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, 5), m_GOOSE.at(row).s_APPID);
			connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}
		if (str.length()<4)
		{
			int i = 4 - str.length();
			for (int j = 0; j<i; j++)
			{
				str = "0" + str;
			}
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, 5), str);
		}
	}
	else if (column==6)
	{

		if ((0xFFF < str.toUInt(&ok, 16)))
		{
			QMessageBox::about(0, tr("Error"), tr("VLAN ID  must be between 000-FFF"));
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, 5), m_GOOSE.at(row).s_APPID);
			connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));

			return;
		}
		if (str.length()<3)
		{
			int i = 3 - str.length();
			for (int j = 0; j<i; j++)
			{
				str = "0" + str;
			}
			ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), str);

		}
	}
	else if (column==7)
	{
		for (int i = 0; i < str.length(); i++)
		{
			QChar chr;
			chr = str.at(i);
			if (!chr.isNumber())
			{
				QMessageBox::about(0, tr("Error"), tr("The VLAN-PRIORITY only can be number"));
				ModelIED_GOOE->setData(ModelIED_GOOE->index(row, column), m_GOOSE.at(row).s_VLAN_PRIORITY);
				connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));

				return;
			}
		}
	}
    connect(ModelIED_GOOE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGOOSEDataChanged(const QModelIndex &, const QModelIndex &)));

}
void MMSExtra::OnSMVDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	int row = topLeft.row();
	int column = topLeft.column();
	QString str;
	bool ok;
	disconnect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
	str = ModelIED_SMV->data(ModelIED_SMV->index(row, column)).toString();
	if (column == 4)
	{
		if ((str.isEmpty()))
		{
			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
			ModelIED_SMV->setData(ModelIED_SMV->index(row, column), m_SMV.at(row).s_MAC_addr);
			connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}

		if (str.count("-") != 5)
		{
			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
			ModelIED_SMV->setData(ModelIED_SMV->index(row, column), m_SMV.at(row).s_MAC_addr);
			connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}
		QStringList listNum = str.split("-", QString::SkipEmptyParts);
		qint8 bCount = listNum.count();

		if (bCount != 6)
		{
			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
			ModelIED_SMV->setData(ModelIED_SMV->index(row, column), m_SMV.at(row).s_MAC_addr);
			connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}

		for (int i = 0; i < bCount; i++)
		{
			bool bret;
			int iNum;
			iNum = listNum[i].toInt(&bret, 16);

			if (!bret)
			{
				QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
				ModelIED_SMV->setData(ModelIED_SMV->index(row, column), m_SMV.at(row).s_MAC_addr);
				connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
				return;
			}

			if ((iNum > 0xFF))
			{
				QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address\nMAC should be XX::XX::XX::XX::XX::XX,XX is between 00-FF"));
				ModelIED_SMV->setData(ModelIED_SMV->index(row, column), m_SMV.at(row).s_MAC_addr);
				connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
				return;
			}
		}
		if (listNum.at(5).length()<2)
		{
			listNum[5] = "0" + listNum[5];
			str.clear();
			str = listNum.at(0);
			for (int m = 1; m < listNum.size(); m++)
			{
				str += "-" + listNum.at(m);
			}
			ModelIED_SMV->setData(ModelIED_SMV->index(row, column), str);
			connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}

	}
	else if (column == 5)
	{

		if ((0x3FFF>str.toUInt(&ok, 16)) || (0xFFFF<str.toUInt(&ok, 16)))

		{
            QMessageBox::about(0, tr("Error"), tr("APPID of SMV must be between 4000-7FFF"));
			ModelIED_SMV->setData(ModelIED_SMV->index(row, 5), m_SMV.at(row).s_APPID);
			connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));
			return;
		}
		if (str.length()<4)
		{
			int i = 4 - str.length();
			for (int j = 0; j<i; j++)
			{
				str = "0" + str;
			}
			ModelIED_SMV->setData(ModelIED_SMV->index(row, 5), str);
		}
	}
	else if (column == 6)
	{

		if ((0xFFF < str.toUInt(&ok, 16)))
		{
			QMessageBox::about(0, tr("Error"), tr("VLAN ID  must be between 000-FFF"));
			ModelIED_SMV->setData(ModelIED_SMV->index(row, 5), m_SMV.at(row).s_APPID);
			connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));

			return;
		}
		if (str.length()<3)
		{
			int i = 3 - str.length();
			for (int j = 0; j<i; j++)
			{
				str = "0" + str;
			}
			ModelIED_SMV->setData(ModelIED_SMV->index(row, column), str);

		}
	}
	else if (column == 7)
	{
		for (int i = 0; i < str.length(); i++)
		{
			QChar chr;
			chr = str.at(i);
			if (!chr.isNumber())
			{
				QMessageBox::about(0, tr("Error"), tr("The VLAN-PRIORITY only can be number"));
				ModelIED_SMV->setData(ModelIED_SMV->index(row, column), m_SMV.at(row).s_VLAN_PRIORITY);
				connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));

				return;
			}
		}
	}
	//if (column == 4)
	//{
	//	QString str = ModelIED_SMV->data(ModelIED_SMV->index(row, column)).toString();
	//	int state = CheckMac(str);
	//	if (state == DO_FAIL)
	//	{
	//		ModelIED_SMV->setData(ModelIED_SMV->index(row, 4), m_SMV.at(row).s_MAC_addr);

	//	}
	//}
	//else
	//{
	//	if ((column == 7) )
	//	{
	//		QString str = ModelIED_SMV->data(ModelIED_SMV->index(row, column)).toString();
	//		QChar chr;
	//		for (int i = 0; i < str.length(); i++)
	//		{
	//			chr = str.at(i);
	//			if (!chr.isNumber())
	//			{
	//				QMessageBox::about(0, tr("Error"), tr("Only can input number "));
	//				ModelIED_SMV->setData(ModelIED_SMV->index(i, 7), m_SMV.at(row).s_VLAN_PRIORITY);
	//				break;
	//			}
	//		}

	//	}
	//	else if (column == 5)
	//	{
	//		QString str = ModelIED_SMV->data(ModelIED_SMV->index(row, column)).toString();
	//		int state = CheckGOOSEID(str);
	//		if (state == DO_FAIL)
	//		{
	//			ModelIED_SMV->setData(ModelIED_SMV->index(row, 5), m_SMV.at(row).s_APPID);

	//		}
	//	}
	//	else if (column == 6)
	//	{
	//		QString str = ModelIED_SMV->data(ModelIED_SMV->index(row, column)).toString();
	//		int state = CheckVLAN(str);
	//		if (state == DO_FAIL)
	//		{
	//			ModelIED_SMV->setData(ModelIED_SMV->index(row, 6), m_GOOSE.at(row).s_VLAN_ID);

	//		}
	//	}
	//}
	connect(ModelIED_SMV, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnSMVDataChanged(const QModelIndex &, const QModelIndex &)));

}

void MMSExtra::onpushbutton_apply()
{
    ConnectAP.iP_addr.clear();
    QString str;
    str = ModelIED_MMS->data(ModelIED_MMS->index(0,2)).toString();
    ConnectAP.iP_addr.s_IP= str;
    str = ModelIED_MMS->data(ModelIED_MMS->index(0,3)).toString();
    ConnectAP.iP_addr.s_AP_Title= str;
    str = ModelIED_MMS->data(ModelIED_MMS->index(0,4)).toString();
    ConnectAP.iP_addr.s_AE_Qualifier= str;
    str = ModelIED_MMS->data(ModelIED_MMS->index(0,5)).toString();
    ConnectAP.iP_addr.s_PSEL= str;
    str = ModelIED_MMS->data(ModelIED_MMS->index(0,6)).toString();
    ConnectAP.iP_addr.s_SSEL= str;
    str = ModelIED_MMS->data(ModelIED_MMS->index(0,7)).toString();
    ConnectAP.iP_addr.s_TSEL= str;
    str = ModelIED_MMS->data(ModelIED_MMS->index(0,7)).toString();
	m_GOOSE.clear();
	for (int i = 0; i<ModelIED_GOOE->rowCount(); i++)
    {
        Address_GOOSE m_data;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,2)).toString();
        m_data.s_cbName = str;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,3)).toString();
        m_data.s_ldInst = str;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,4)).toString();
       
		QStringList list = str.split("-", QString::SkipEmptyParts);
		if (list.at(5).length()<2)
		{
			list[5] = "0" + list[5];
		}
		str.clear();
		str += list.at(0);
		for (int m = 1; m< list.size(); m++)
		{
			str +="-"+ list.at(m);
		}
		m_data.s_MAC_addr = str;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,5)).toString();
        m_data.s_APPID = str;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,6)).toString();
        m_data.s_VLAN_ID = str;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,7)).toString();
        m_data.s_VLAN_PRIORITY = str;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,8)).toString();
        m_data.s_MinTime = str;
        str = ModelIED_GOOE->data(ModelIED_GOOE->index(i,9)).toString();
        m_data.s_MaxTime = str;
        m_GOOSE.append(m_data);
    }
    m_SMV.clear();
	for (int i = 0; i<ModelIED_SMV->rowCount(); i++)
    {
        Address_SMV m_data;
        str = ModelIED_SMV->data(ModelIED_SMV->index(i,2)).toString();
        m_data.s_cbName = str;
        str = ModelIED_SMV->data(ModelIED_SMV->index(i,3)).toString();
        m_data.s_ldInst = str;
        str=ModelIED_SMV->data(ModelIED_SMV->index(0,4)).toString();
		QStringList list = str.split("-", QString::SkipEmptyParts);
		if (list.at(5).length()<2)
		{
			list[5] = "0" + list[5];
		}
		str.clear();
		str += list.at(0);
		for (int m = 1; m< list.size(); m++)
		{
			str += "-" + list.at(m);
		}
        m_data.s_MAC_addr = str;
        str=ModelIED_SMV->data(ModelIED_SMV->index(0,5)).toString();
        m_data.s_APPID =str;
        str=ModelIED_SMV->data(ModelIED_SMV->index(0,6)).toString();
        m_data.s_VLAN_ID =str;
        str=ModelIED_SMV->data(ModelIED_SMV->index(0,7)).toString();
        m_data.s_VLAN_PRIORITY =str;

        m_SMV.append(m_data);
    }
    m_Point->UpdataConnectAPMMS(ConnectAP,m_GOOSE,m_SMV);
    //    if(CheckIP(ui->lineEdit_IP->text())==DO_FAIL)
	//    {
	//        return;
	//    }

	//	bool OK;

	//	ConnectAP.iP_addr.s_AE_Qualifier=ui->lineEdit_AE->text();
	//	ConnectAP.iP_addr.s_IP=ui->lineEdit_IP->text();
	//	ConnectAP.iP_addr.s_PSEL=ui->lineEdit_PSEL->text();
	//	ConnectAP.iP_addr.s_SSEL=ui->lineEdit_SSEL->text();
	//	ConnectAP.iP_addr.s_AP_Title=ui->lineEdit_Title->text();
	//	ConnectAP.iP_addr.s_TSEL=ui->lineEdit_TSEL->text();

	//    if(!ConnectAP.Goose_addr.isEmpty())
	//    {
	//		if (ChenkMac(ui->lineEdit_MACG->text()) == DO_FAIL)
	//		{
	//			return;
	//		}
	//        ConnectAP.Goose_addr.s_APPID = ui->lineEdit_APPIDG->text();
	//        ConnectAP.Goose_addr.s_MAC_addr=ui->lineEdit_MACG->text();
	//        ConnectAP.Goose_addr.s_MaxTime=ui->lineEdit_MAXG->text();
	//        ConnectAP.Goose_addr.s_MinTime=ui->lineEdit_MING->text();
	//        ConnectAP.Goose_addr.s_VLAN_ID=ui->lineEdit_VLAN_IDG->text();
	//        if(ConnectAP.Goose_addr.s_VLAN_ID.length()<3)
	//        {
	//            QMessageBox::about(0, tr("Error"), tr("VLAN ID must be between 000-FFF"));
	//            return;
	//        }
	//        ConnectAP.Goose_addr.s_VLAN_PRIORITY=ui->lineEdit_VLAN_PRIG->text();
	//        if ((0x3FFF < ConnectAP.Goose_addr.s_APPID.toUInt(&OK, 16)) || (0x0000 > ConnectAP.Goose_addr.s_APPID.toUInt(&OK, 16)))
	//        {
	//            QMessageBox::about(0, tr("Error"), tr("APPID of GOOSE must be between 0-3FFF"));
	//            return;
	//        }
	//    }

	//    if(!ConnectAP.SMV_addr.isEmpty())
	//    {
	//		if (ChenkMac(ui->lineEdit_MACS->text()) == DO_FAIL)
	//		{
	//			return;
	//		}
	//        ConnectAP.SMV_addr.s_MAC_addr=ui->lineEdit_MACS->text();
	//        ConnectAP.SMV_addr.s_MaxTime=ui->lineEdit_MAXS->text();
	//        ConnectAP.SMV_addr.s_MinTime=ui->lineEdit_MINS->text();
	//        ConnectAP.SMV_addr.s_VLAN_ID=ui->lineEdit_VLAN_IDS->text();
	//        ConnectAP.SMV_addr.s_VLAN_PRIORITY=ui->lineEdit_VLAN_PRIS->text();
	//        if(ConnectAP.SMV_addr.s_VLAN_ID.length()<3)
	//        {
	//            QMessageBox::about(0, tr("Error"), tr("VLAN ID must be between 000-FFF"));
	//            return;
	//        }
	//        ConnectAP.SMV_addr.s_APPID=ui->lineEdit_APPIDS->text();

	//        if ((0x3FFF>ConnectAP.SMV_addr.s_APPID.toUInt(&OK, 16)) || (0xFFFF<ConnectAP.SMV_addr.s_APPID.toUInt(&OK, 16)))
	//        {
	//            QMessageBox::about(0, tr("Error"), tr("APPID of SMV must be between 4000-7FFF"));
	//             return;
	//        }
	//    }

	accept();
}
void MMSExtra::onpushbutton_cancel()
{
	reject();
}
int MMSExtra::CheckIP(QString strIPAddr, int row, int column)
{
	if ((strIPAddr.isEmpty()))
	{
		return DO_FAIL;
	}

	if (strIPAddr.count(".") != 3)
	{
		QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
		ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_IP);
		return DO_FAIL;
	}

	QStringList listNum = strIPAddr.split(".", QString::SkipEmptyParts);
	qint8 bCount = listNum.count();

	if (bCount != 4)
	{
		QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
		ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_IP);
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
			ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_IP);
			return DO_FAIL;
		}
		if (i == 0)
		{
			if (iNum == 0)
			{
				QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
				ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_IP);
				return DO_FAIL;
			}

		}
		if ((iNum > 255))
		{
			QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
			ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_IP);
			return DO_FAIL;
		}
	}
	if ((listNum[0].toInt(&bret) == 0) && (listNum[1].toInt(&bret) == 0)&&(listNum[2].toInt(&bret) == 0)&&(listNum[3].toInt(&bret) == 0))
	{
		QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
		ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_IP);
		return DO_FAIL;
	}
	if ((listNum[0].toInt(&bret) == 127) && (listNum[1].toInt(&bret) == 0) && (listNum[2].toInt(&bret) == 0) && (listNum[3].toInt(&bret) == 1))
	{
		QMessageBox::about(0, tr("Error"), tr("Wrong IP Address"));
		ModelIED_MMS->setData(ModelIED_MMS->index(row, column), ConnectAP.iP_addr.s_IP);
		return DO_FAIL;
	}
	return DO_OK;
}

//int MMSExtra::CheckMac(QString strMAC)
//{
//	if ((strMAC.isEmpty()))
//	{
//		return DO_FAIL;
//	}
//
//	if (strMAC.count("-") != 5)
//	{
//		QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address"));
//		return DO_FAIL;
//	}
//	QStringList listNum = strMAC.split("-", QString::SkipEmptyParts);
//	qint8 bCount = listNum.count();
//
//	if (bCount != 6)
//	{
//		QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address"));
//		return DO_FAIL;
//	}
//	if (listNum.at(5).length()<2)
//	{
//		listNum[5] = "0" + listNum.at(5);
//	}
//	for (int i = 0; i < bCount; i++)
//	{
//		bool bret;
//		int iNum;
//		iNum = listNum[i].toInt(&bret, 16);
//
//		if (!bret)
//		{
//			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address"));
//			return DO_FAIL;
//		}
//
//		if ((iNum > 0xFF))
//		{
//			QMessageBox::about(0, tr("Error"), tr("Wrong MAC Address"));
//			return DO_FAIL;
//		}
//	}
//	return DO_OK;
//}
//int MMSExtra::CheckVLAN(QString strVLANID)
//{
//	long hex;
//	bool ok;
//	QString str = "FFF";
//	hex = strVLANID.toLong(&ok, 16);
//	if (hex>str.toLong(&ok, 16))
//	{
//		return DO_FAIL;
//	}
//	return DO_OK;
//}
//int MMSExtra::CheckSMVID(QString SMVID)
//{
//	long hex;
//	bool ok;
//	QString str1 = "4000";
//	QString str2 = "7FFF";
//	hex = SMVID.toLong(&ok, 16);
//	if ((hex > str2.toLong(&ok, 16)) || (hex< str1.toLong(&ok, 16)))
//	{
//		return DO_FAIL;
//	}
//	return DO_OK;
//
//}
//int MMSExtra::CheckGOOSEID(QString GOOSEID)
//{
//	long hex;
//	bool ok;
//	QString str = "3FFF";
//	hex = GOOSEID.toLong(&ok, 16);
//	if ((hex > str.toLong(&ok, 16)) || (hex<0))
//	{
//		return DO_FAIL;
//	}
//	return DO_OK;
//}

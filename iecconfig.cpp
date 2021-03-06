﻿#include "iecconfig.h"
#include "ui_iecconfig.h"

IECCONFIG::IECCONFIG(QWidget *parent) :
QDialog(parent),
ui(new Ui::IECCONFIG)
{
	ui->setupUi(this);
	Creat_flag = 0;
	Save_flag = true;
	Point = new XML();
	m_ModelDEV = new QStandardItemModel;
	headerlist << tr("Name") << tr("IP1") << tr("IP2");
	GetDeviceList();
	connect(ui->pushButton_add, SIGNAL(clicked(bool)), this, SLOT(pushbutton_Add_click()));
	connect(ui->pushButton_del, SIGNAL(clicked(bool)), this, SLOT(pushbutton_Del_click()));
	connect(ui->pushButton_new, SIGNAL(clicked(bool)), this, SLOT(pushbutton_New_click()));
	connect(ui->pushButton_save, SIGNAL(clicked(bool)), this, SLOT(pushbutton_Save_click()));
	connect(ui->pushButton_station, SIGNAL(clicked(bool)), this, SLOT(pushbutton_Station_click()));
	connect(ui->pushButton_time, SIGNAL(clicked(bool)), this, SLOT(pushbutton_Time_click()));
	connect(ui->radioButton_browse, SIGNAL(clicked(bool)), this, SLOT(RadioButton_browse_click()));
	connect(ui->radioButton_new, SIGNAL(clicked(bool)), this, SLOT(RadioButton_new_click()));
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(OnDatadoubleClicked(const QModelIndex &)));

	ui->pushButton_add->setEnabled(false);
	ui->pushButton_del->setEnabled(false);
	ui->pushButton_save->setEnabled(false);
	ui->pushButton_time->setEnabled(false);
	ui->pushButton_station->setEnabled(false);
}

IECCONFIG::~IECCONFIG()
{
	delete ui;

}
void IECCONFIG::Init_dlg()
{
	ui->groupBox->setTitle(tr("IECconfig"));
	ui->pushButton_add->setText(tr("Add"));
	ui->pushButton_del->setText(tr("Del"));
	ui->pushButton_new->setText(tr("New"));
	ui->pushButton_save->setText(tr("Save"));
	ui->pushButton_time->setText(tr("Time Server"));
	ui->label->setText(tr("File:"));
	ui->radioButton_new->setText(tr("New"));
	ui->radioButton_browse->setText(tr("Browse"));
	ui->pushButton_station->setText(tr("Station Para"));
	ui->radioButton_new->setChecked(true);
	ui->radioButton_new->clicked();
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	//ui->tableView->setAcceptDrops(true);
	m_ModelDEV->clear();
	m_ModelDEV->setColumnCount(headerlist.count());
	ui->tableView->setToolTip(tr("Double Click to Check detail"));
	ui->tableView->setModel(m_ModelDEV);
	for (int i = 0; i < headerlist.count(); i++)
	{
		m_ModelDEV->setHeaderData(i, Qt::Horizontal, headerlist.at(i));

	}

	ui->tableView->setColumnWidth(0, 200);
	ui->tableView->setColumnWidth(1, 200);
	ui->tableView->setColumnWidth(2, 200);
	//	disconnect(ui->SETTable, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(RowDoubleClicked(const QModelIndex &)));

}
void IECCONFIG::pushbutton_New_click()
{
	if (Save_flag == false)
	{
		QMessageBox msgBox;
		msgBox.setText("The IEC file has not been saved");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Save)
		{
			ui->pushButton_save->clicked();
			return;
		}
	}
	if (Creat_flag == 1)
	{
		if (Point==NULL)
		{
			Point = new XML;
		}
		Point->CreatXML(2);
		ui->pushButton_add->setEnabled(true);
		ui->pushButton_del->setEnabled(true);
		ui->pushButton_save->setEnabled(true);
		ui->pushButton_time->setEnabled(true);
		ui->pushButton_station->setEnabled(true);
	}
	else if (Creat_flag == 2)
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open XML"),
			QDir::currentPath(),
			tr("XML Files (*.XML)"));
		if (!fileName.isNull())
		{
			ui->lineEdit->setText(fileName);

			File_IEC = fileName;
			int recode;
			if (Point == NULL)
			{
				Point = new XML;
			}
			recode=Point->LoadXML(fileName, 2);
			if (recode==DO_FAIL)
			{
				ui->lineEdit->clear();
				File_IEC.clear();
				ui->pushButton_add->setEnabled(false);
				ui->pushButton_del->setEnabled(false);
				ui->pushButton_save->setEnabled(false);
				ui->pushButton_time->setEnabled(false);
				ui->pushButton_station->setEnabled(false);
				return;
			}
			ui->pushButton_add->setEnabled(true);
			ui->pushButton_del->setEnabled(true);
			ui->pushButton_save->setEnabled(true);
			ui->pushButton_time->setEnabled(true);
			ui->pushButton_station->setEnabled(true);
            DisplayDevice();
		}
else
{
	delete Point;
	Point = NULL;
	m_ModelDEV->setRowCount(0);
	ui->lineEdit->clear();
	File_IEC.clear();
	ui->pushButton_add->setEnabled(false);
	ui->pushButton_del->setEnabled(false);
	ui->pushButton_save->setEnabled(false);
	ui->pushButton_time->setEnabled(false);
	ui->pushButton_station->setEnabled(false);
}
	}


	return;
}

void IECCONFIG::pushbutton_Add_click()
{
	ApplyOneIED m_dlg;
	m_dlg.DeviceType_List = DeviceType_List;
	m_dlg.CreatOneIED();
	m_dlg.Init_dlg(0);
    m_dlg.IEDlist=IED_List;
	m_dlg.DisplayDevice(0);
	m_dlg.Point = Point;
	if (m_dlg.exec() == QDialog::Accepted)
	{
		RemoteAddress_Type RemoteAddres = m_dlg.RemoteAddres;
		IED_IEC IED = m_dlg.IED;

		Point->CreatOneRemote(IED, RemoteAddres);
		Save_flag = false;
	}
	DisplayDevice();
}

void IECCONFIG::pushbutton_Del_click()
{
	QStringList namelist;
	selectMode = ui->tableView->selectionModel();

	QModelIndexList indexes;
	indexes.clear();
	indexes = selectMode->selectedRows();
	QModelIndex index;
	foreach(index, indexes)
	{
		namelist.append(m_ModelDEV->data(m_ModelDEV->index(index.row(), 0)).toString());
	}
	for (int i = 0; i < namelist.size(); i++)
	{
		Point->DelOneRemote(namelist[i]);
	}
	Save_flag = false;
	DisplayDevice();
}

void IECCONFIG::pushbutton_Save_click()
{
	if (!File_IEC.isEmpty())
	{
		Point->SaveXML(File_IEC);
        QMessageBox::about(0, QObject::tr("Notice"), QObject::tr("Save file success"));

	}
	else
	{
		QString fileName = QFileDialog::getSaveFileName(this,
			tr("Open XML"),
			"",
			tr("XML Files (*.XML)"));
		if (!fileName.isNull())
		{
			ui->lineEdit->setText(fileName);
			File_IEC = fileName;
			Point->SaveXML(fileName);
		}

	}
	//ui->radioButton_new->setChecked(false);
	ui->radioButton_browse->clicked();
	ui->radioButton_browse->setChecked(true);
	Save_flag = true;
}

void IECCONFIG::pushbutton_Time_click()
{
	TimeServer m_Timeserver;
	Point->GetTimeService(m_Timeserver);
	TimeService m_dlg;
	m_dlg.m_timeserver = m_Timeserver;
	m_dlg.Display();
	if (m_dlg.exec() == QDialog::Accepted)
	{
		m_Timeserver = m_dlg.m_timeserver;
		Point->UpdateTimeService(m_Timeserver);
		Save_flag = false;
		return;
	}

}

void IECCONFIG::pushbutton_Station_click()
{
	StationPara m_dlg;
	StationPara_struct m_data;
	Point->GetStationPara(m_data, 2);
	m_dlg.vendor = m_data.Vender;
	m_dlg.Version = m_data.Version;
	m_dlg.ProjectName = m_data.ProjectName;
	m_dlg.Line = m_data.Line;
	m_dlg.display(2);
	if (m_dlg.exec() == QDialog::Accepted)
	{
		m_data.Vender = m_dlg.vendor;
		m_data.Version = m_dlg.Version;
		m_data.Line = m_dlg.Line;
		m_data.ProjectName = m_dlg.ProjectName;
		Point->UpdataStationPara(m_data);
		Save_flag = false;
		return;
	}
}
void IECCONFIG::RadioButton_browse_click()
{
	ui->pushButton_new->setText(tr("Browse"));

	Creat_flag = 2;
}
void IECCONFIG::RadioButton_new_click()
{
	ui->pushButton_new->setText(tr("New"));
	Creat_flag = 1;
}
void IECCONFIG::OnDataChanged(const QModelIndex & StartIndex, const QModelIndex &EndIndex)
{

}
void IECCONFIG::GetDeviceList()
{
	DeviceType_List.clear();
	Point->GetDeviceTypeList(DeviceType_List);
}
void IECCONFIG::DisplayDevice()
{
	m_ModelDEV->setRowCount(0);
	QVector< IED_IEC> IEDList;
	QVector< RemoteAddress_Type>RemoteList;
	int ret = Point->GetDeviceList(IEDList, RemoteList);
	if (ret == DO_FAIL)
	{
		return;

	}
	for (int i = 0; i < IEDList.size(); i++)
	{
		m_ModelDEV->setRowCount(m_ModelDEV->rowCount() + 1);
		m_ModelDEV->setData(m_ModelDEV->index(i, 0), QVariant(IEDList[i].Name));
		m_ModelDEV->setData(m_ModelDEV->index(i, 1), QVariant(RemoteList[i].Addr1));
		m_ModelDEV->setData(m_ModelDEV->index(i, 2), QVariant(RemoteList[i].Addr2));
		m_ModelDEV->item(i, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ModelDEV->item(i, 1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ModelDEV->item(i, 2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}

}
void IECCONFIG::OnDatadoubleClicked(const QModelIndex & index)
{
	QVector< IED_IEC> IEDList;
	QVector< RemoteAddress_Type>RemoteList;
	QString strname = m_ModelDEV->data(m_ModelDEV->index(index.row(), 0)).toString();
	int ret = Point->GetDeviceList(IEDList, RemoteList);
	IED_IEC m_IED;
	RemoteAddress_Type m_Remote;
	for (int i = 0; i < IEDList.size(); i++)
	{
		if (0 == strcmp(strname.toStdString().data(), IEDList[i].Name.toStdString().data()))
		{
			m_IED = IEDList[i];
			m_Remote = RemoteList[i];
			break;
		}
	}
	ApplyOneIED m_dlg;
	m_dlg.DeviceType_List = DeviceType_List;
	m_dlg.IED = m_IED;
	m_dlg.RemoteAddres = m_Remote;
	m_dlg.Init_dlg(0);
    m_dlg.IEDlist=IED_List;
	m_dlg.DisplayDevice(2);
	m_dlg.Point = Point;
	if (m_dlg.exec() == QDialog::Accepted)
	{
		RemoteAddress_Type RemoteAddres = m_dlg.RemoteAddres;
		IED_IEC IED = m_dlg.IED;
		QString OldName = m_dlg.OldName;
		Point->UpdateRemote(OldName, IED, RemoteAddres);
		Save_flag = false;
	}
	DisplayDevice();

}

﻿#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::InputDialog)
{
	ui->setupUi(this);
	//QDesktopWidget *wgite = QApplication::desktop();
	//int iwidth = wgite->width();
	//int iheight = wgite->height();
	//this->resize(iwidth, iheight-100);
	ui->treeWidget_local->setSelectionMode(QAbstractItemView::ExtendedSelection);
	ui->treeWidget_ex->setSelectionMode(QAbstractItemView::ExtendedSelection);
	m_Menu = new QMenu(this);
	actionDel = new QAction(tr("Del"), this);
	m_Menu->addAction(actionDel);
	this->setWindowTitle(tr("Virtual terminal Mapping"));
    ui->pushButton_fresh->setText(tr("Fresh"));
    ui->pushButton_fresh_ex->setText(tr("Fresh"));
	connect(ui->dropTable, SIGNAL(senddragMoveEvent(QDropEvent*)), this, SLOT(receivedragEnterEvent(QDropEvent*)));
	connect(ui->comboBox_localLD, SIGNAL(activated(QString)), this, SLOT(Combox_Local_LD_Active(QString)));
	connect(ui->comboBox_localLN, SIGNAL(activated(QString)), this, SLOT(Combox_Local_LN_Active(QString)));
	connect(ui->comboBox_localAP, SIGNAL(activated(QString)), this, SLOT(Combox_Local_AP_Active(QString)));
	connect(ui->comboBox_exLD, SIGNAL(activated(QString)), this, SLOT(Combox_Ex_LD_Active(QString)));
	connect(ui->comboBox_exAP, SIGNAL(activated(QString)), this, SLOT(Combox_Ex_AP_Active(QString)));
	connect(ui->comboBox_exIED, SIGNAL(currentIndexChanged(QString)), this, SLOT(Combox_Ex_IED_Active(QString)));
	connect(ui->pushButton_fresh, SIGNAL(clicked()), this, SLOT(onpushbutton_fresh_Receiver()));
	connect(ui->pushButton_fresh_ex, SIGNAL(clicked()), this, SLOT(onpushbutton_fresh_Sender()));
	connect(ui->treeWidget_local, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
		this, SLOT(itemDoubleClicked(QTreeWidgetItem*, int)));
	connect(ui->dropTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(DropTable_MousEvent(QPoint)));
	connect(actionDel, SIGNAL(triggered()), this, SLOT(OnAction_Del()));
	ui->splitter->setStretchFactor(0, 50);
	ui->splitter->setStretchFactor(1, 50);
}

InputDialog::~InputDialog()
{
	delete ui;
	if (m_ModelDate != NULL)
	{
		delete m_ModelDate;
	}
}
void InputDialog::Init_dlg()
{
	QString str;

	str = tr("receiver") + strcuried;
	ui->frame->setToolTip(str);
	ui->frame_2->setToolTip(tr("External signal"));
	ui->label_exAP->setText(tr("Access Point"));
	ui->label_exAP->hide();
	ui->label_localAP->setText(tr("Access Point"));
	ui->label_exDA->setText(tr("DA Keyword"));
	ui->label_exDA->hide();
	ui->label_localDA->setText(tr("DA Keyword"));
	ui->label_exFC->setText(tr("FC limit"));

	ui->label_localFC->setText(tr("FC limit"));
	ui->label_exIED->setText(tr("IED Choice"));
	ui->label_exLD->setText(tr("LD"));
	ui->label_exLD->hide();
	ui->label_localLD->setText(tr("LD"));
	ui->label_exLN->setText(tr("LN"));
	ui->label_exLN->hide();
	ui->label_localLN->setText(tr("LN"));
	ui->checkBox1_DA->setText(tr("Must DA"));
	ui->checkBox1_DA->setChecked(true);
	ui->checkBox1_DA->setEnabled(false);
	ui->checkBox1_DAEND->setText(tr("End of DA"));
	ui->checkBox1_DAEND->setChecked(true);
	ui->checkBox1_DAEND->setEnabled(false);
	ui->checkBox1_disp->setText(tr("Not display Common"));
	ui->checkBox1_disp->setChecked(true);
	ui->checkBox1_disp->setEnabled(false);
	ui->checkBox2_DA->setText(tr("Must DA"));
	ui->checkBox2_DA->setCheckable(true);
	ui->checkBox2_DA->setEnabled(false); \
		ui->checkBox2_DA->hide();
	ui->checkBox2_DAEND->setText(tr("End of DA"));
	ui->checkBox2_DAEND->setCheckable(true);
	ui->checkBox2_DAEND->setEnabled(false);
	ui->checkBox2_DAEND->hide();
	ui->checkBox2_disp->setText(tr("Not display Common"));
	ui->checkBox2_disp->setCheckable(true);
	ui->checkBox2_disp->setEnabled(false);
	ui->checkBox2_disp->hide();
	ui->comboBox_exAP->hide();
	ui->comboBox_exLD->hide();
	ui->comboBox_exLN->hide();
	ui->dropTable->setAcceptDrops(true);
	ui->lineEdit_localDA->clear();
	ui->lineEdit_localDA->setText(tr("stVal|mag|instMag|f|i"));
	ui->lineEdit_exDA->clear();
	ui->lineEdit_exDA->setText(tr("dsSV|dsGOOSE"));
	//ui->lineEdit_exDA->setText(tr("stVal|mag|instMag|f|i"));
	ui->treeWidget_local->setDragDropMode(QAbstractItemView::DragOnly);
	ui->treeWidget_ex->setDragDropMode(QAbstractItemView::DragOnly);
	ui->comboBox_exFC->clear();
	ui->comboBox_localFC->clear();

	QStringList fclist;
	fclist << tr("ST") << tr("MX") << tr("CO") << tr("CF") << tr("DC") << tr("SP") << tr("SG") << tr("RP") << tr("LG") << tr("BR") << tr("GO")
		<< tr("GS") << tr("SV") << tr("SE") << tr("MS") << tr("SC") << tr("US");
	ui->comboBox_localFC->addItems(fclist);
	ui->comboBox_exFC->addItems(fclist);

	m_ModelDate = new QStandardItemModel;
	//m_ModelSlection = new QItemSelectionModel;
	headerlist.clear();
	headerlist << tr("intAddr") << tr("intDesc") << tr("exIED") << tr("exAddr") << tr("exDesc");


	ui->dropTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->dropTable->setSelectionMode(QAbstractItemView::ExtendedSelection);

	m_ModelDate->clear();


	disconnect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));
	m_ModelDate->setColumnCount(headerlist.count());

	ui->dropTable->setModel(m_ModelDate);
	for (int i = 0; i < headerlist.count(); i++)
	{
		m_ModelDate->setHeaderData(i, Qt::Horizontal, headerlist.at(i));

	}
	QDesktopWidget *wgite = QApplication::desktop();
	
    int iwidth = wgite->width();
	ui->dropTable->setColumnWidth(0, 200);
	ui->dropTable->setColumnWidth(1, 200);
	ui->dropTable->setColumnWidth(2, 100);
	ui->dropTable->setColumnWidth(3, 200);
	ui->dropTable->setColumnWidth(4, 200);
	connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));
	Init_Ex_IED(strcuried);
	Init_local_AP(strcuried);

	headerlist.clear();
	headerlist << "Object" << "Desc";

	ui->treeWidget_local->setHeaderLabels(headerlist);
	ui->treeWidget_local->setColumnWidth(0, 200);
	ui->treeWidget_local->setColumnWidth(1, 60);
	ui->treeWidget_ex->setHeaderLabels(headerlist);
	ui->treeWidget_ex->setColumnWidth(0, 200);
	ui->treeWidget_ex->setColumnWidth(1, 60);
	//this->resize(QSize(800, 600));
}
void InputDialog::receivedragEnterEvent(QDropEvent *event)
{
	QString str1, str2, str3;
	str1 = event->source()->objectName();
	str2 = ui->treeWidget_ex->objectName();
	str3 = ui->treeWidget_local->objectName();
	QModelIndex curIndex = ui->dropTable->indexAt(event->pos());
	if (!curIndex.isValid())
	{
		return;
	}
	//QString str4;

	if (str1 == str2)
	{
		Change_type = EX_DATA;
		FreshData(curIndex, EX_DATA);
	}
	if (str1 == str3)
	{
		Change_type = LOCAL_DATA;
		FreshData(curIndex, LOCAL_DATA);
	}
	Display_Input_Ln();
	return;
}
void InputDialog::FreshData(QModelIndex curIndex, int source)
{
	if (m_ModelDate->rowCount() == 0)
	{
		return;
	}
	QVector<FCDA_Struct> data_list;
	if (source == LOCAL_DATA)
	{
		QList<QTreeWidgetItem*> itemlist;

		QTreeWidgetItem *root = ui->treeWidget_local->invisibleRootItem();
		int index = 0;
		itemlist = ui->treeWidget_local->selectedItems();
		for (int i = 0; i < itemlist.size(); i++)
		{
			FCDA_Struct m_data;
			index = root->indexOfChild(itemlist[i]);
			m_data = DataInstList_Select_local[index];
			data_list.append(m_data);

		}

		FreshInputOfTable(curIndex, data_list, source);

	}
	if (source == EX_DATA)
	{
		QList<QTreeWidgetItem*> itemlist;
		QTreeWidgetItem* DataSetItem;
		DataSetStruct m_dataSet;
		//QStringList instlist;
		int index = 0;
		itemlist = ui->treeWidget_ex->selectedItems();
		DataSetItem = itemlist[0]->parent();
		for (int i = 0; i < DataSetVector.size(); i++)
		{
			if (DataSetItem->text(0) == DataSetVector[i].DataSetName)
			{
				m_dataSet = DataSetVector[i];
			}
		}
		for (int i = 0; i < itemlist.size(); i++)
		{
			//QString str;
			//str = itemlist[i]->text(0);
			index = itemlist[0]->parent()->indexOfChild(itemlist[i]);
			data_list.append(m_dataSet.FCDA_List[index]);
		}

		FreshInputOfTable(curIndex, data_list, source);
	}
}
void InputDialog::Init_local_AP(QString str)
{
	m_scdpoint->GetIEDByname(str);
	m_scdpoint->GetChild("AccessPoint");
	QString str1;
	QStringList strlist;
	strlist.clear();
	str1 = m_scdpoint->GetAttribute("name");
	strlist.append(str1);
	while (m_scdpoint->GetNextChild("AccessPoint") == DO_OK)
	{
		str1 = m_scdpoint->GetAttribute("name");
		strlist.append(str1);
	}
	m_scdpoint->SwitchRoot();
	ui->comboBox_localAP->addItems(strlist);
	ui->comboBox_localAP->activated(0);
	ui->comboBox_localAP->activated(ui->comboBox_localAP->currentText());
}
void InputDialog::onpushbutton_fresh_Receiver()
{
    disconnect(ui->pushButton_fresh, SIGNAL(clicked()), this, SLOT(onpushbutton_fresh_Receiver()));

	QStringList dalist, LntypeList;
	QString strap, strda, strld, strln, str;
	DataInstList_LN_local.clear();
	DataInstList_Select_local.clear();

	QString strfc;
	strda = ui->lineEdit_localDA->text();
	strfc = ui->comboBox_localFC->currentText();
	strap = ui->comboBox_localAP->currentText();
	strld = ui->comboBox_localLD->currentText();
	strln = ui->comboBox_localLN->currentText();
	ui->treeWidget_local->clear();
	if (strda != NULL)
	{
		dalist = strda.split("|");
	}
	//m_scdpoint->GetLNodeTypeList(str, LnodeTyepList);
	m_scdpoint->GetLNodeTypeList(strcuried, strap, strld, strln, LntypeList);
	//QMessageBox::about(0, "notice", LntypeList.at(0));
	m_scdpoint->CreatDataMatrix(LntypeList.at(0), DataMatrix_Vector_LN_Local);
	m_scdpoint->GetDataInstList(strcuried, strap, strld, strln, DataInstList_LN_local);
	FCDA_Struct m_datainst;
	for (int i = 0; i < DataInstList_LN_local.size(); i++)
	{
		m_datainst = DataInstList_LN_local[i];
		if ((0 == strcmp(m_datainst.B_doName, "PhyHealth")) || (0 == strcmp(m_datainst.B_doName, "Mod")) || (0 == strcmp(m_datainst.B_doName, "Beh")) || 0 == strcmp(m_datainst.B_doName, "Health"))
		{
			continue;
		}

		Filter_datainst(m_datainst);

		if (0 != strcmp(m_datainst.B_fc.data(), strfc.toLocal8Bit().data()))
		{
			continue;
		}
		if (dalist.size() != 0)
		{
			bool flag = false;
			for (int j = 0; j < dalist.size(); j++)
			{
				if (m_datainst.B_daName.contains(dalist.at(j).toLocal8Bit()))
				{
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				continue;
			}
		}

		DataInstList_Select_local.append(m_datainst);
	}
	ADDDatainstListTOTree(DataInstList_Select_local);
	//m_datalist_local.clear();
	//      QString strap, strld,strln,strlntype;
	//      LN_InstStruct m_lninst;
	//      strap = ui->comboBox_localAP->currentText();
	//      strld = ui->comboBox_localLD->currentText();
	//      strln = ui->comboBox_localLN->currentText();
	//      int  recode= m_scdpoint->GetIEDByname(strcuried);
	//      recode = m_scdpoint->GetAccessPoint(strap);
	//      recode = m_scdpoint->GetLDnode(strld);
	//      recode = m_scdpoint->GetLNnode(strln);
	//      if (recode == DO_FAIL)
	//      {
	//              m_scdpoint->SwitchToIED();
	//              
	//      }
	//      strlntype = m_scdpoint->GetAttribute("lnType");
	//      m_lninst.B_lnType = strlntype;
	//      m_lninst.B_inst = m_scdpoint->GetAttribute("inst");
	//      m_lninst.B_lnClass = m_scdpoint->GetAttribute("lnClass");
	//      m_lninst.B_prefix = m_scdpoint->GetAttribute("prefix");
	//if (m_scdpoint->GetChild("DOI") == DO_FAIL)
	//      {
	//              m_scdpoint->SwitchToIED();
	//              
	//      }
	//      m_scdpoint->SetRememberEle();
	//m_scdpoint->analyzeDO(m_datalist_local, strln, strlntype);
	//      m_scdpoint->switchRememberEle();
	//while (m_scdpoint->GetNextChild("DOI") != DO_FAIL)
	//      {
	//              m_scdpoint->SetRememberEle();
	//  m_scdpoint->analyzeDO(m_datalist_local, strln, strlntype);
	//              m_scdpoint->switchRememberEle();
	//      }
	//      m_scdpoint->SwitchToIED();

	//ADDListToLocal(m_lninst, m_datalist_local);
    connect(ui->pushButton_fresh, SIGNAL(clicked()), this, SLOT(onpushbutton_fresh_Receiver()));

}

void InputDialog::onpushbutton_fresh_Sender()
{
    disconnect(ui->pushButton_fresh_ex, SIGNAL(clicked()), this, SLOT(onpushbutton_fresh_Sender()));

	DataSetVector.clear();
	ui->treeWidget_ex->clear();
	if (ui->comboBox_exIED->currentIndex() == -1)
	{
		return;
	}
	QVector<DataSetStruct> DataSetVector_No;
	//QString stried, strap, strld, strln, strlntype, str;
	QString strdataset;
	QStringList DataSetList;
	QString stried = ui->comboBox_exIED->currentText();
	strdataset = ui->lineEdit_exDA->text().simplified();
	if (!strdataset.isEmpty())
	{
		DataSetList = strdataset.split("|");
	}
	m_scdpoint->GetDataSetVector(stried, DataSetVector_No);
	for (int i = 0; i < DataSetVector_No.size(); i++)
	{
		if (DataSetList.size() == 0)
		{
			DataSetVector.append(DataSetVector_No[i]);
			continue;
		}
		for (int m = 0; m < DataSetList.size(); m++)
		{
			if (DataSetVector_No[i].DataSetName.contains(DataSetList[m], Qt::CaseInsensitive))
			{
				DataSetVector.append(DataSetVector_No[i]);
			}
		}
	}
	for (int i = 0; i < DataSetVector.size(); i++)
	{
        if(DataSetVector[i].Goose_state!=1)
            continue;
		ADDListToEx(DataSetVector[i]);
	}
	//	LN_InstStruct m_lninst;
	//	Input_Struct m_input;
	//	m_datalist_ex.clear();
	//	stried = ui->comboBox_exIED->currentText();
	//	m_input.B_iedName = stried;
	//	strap = ui->comboBox_exAP->currentText();
	//	strld = ui->comboBox_exLD->currentText();
	//	strln = ui->comboBox_exLN->currentText();
	//	int  recode = m_scdpoint->GetIEDByname(stried);
	//	recode = m_scdpoint->GetAccessPoint(strap);
	//	recode = m_scdpoint->GetLDnode(strld);
	//	str = m_scdpoint->GetAttribute("inst");
	//	recode = m_scdpoint->GetLNnode(strln);
	//	if (recode == DO_FAIL)
	//	{
	//		m_scdpoint->SwitchToIED();
	//		return;

	//	}
	//	strlntype = m_scdpoint->GetAttribute("lnType");
	//	m_lninst.B_lnType = strlntype;
	//	m_input.B_ldInst = str;
	//	m_lninst.B_inst = m_scdpoint->GetAttribute("inst");
	//	m_input.B_lnInst = m_scdpoint->GetAttribute("inst");
	//	m_lninst.B_lnClass = m_scdpoint->GetAttribute("lnClass");
	//	m_input.B_lnClass = m_scdpoint->GetAttribute("lnClass");
	//	m_lninst.B_prefix = m_scdpoint->GetAttribute("prefix");
	//	m_input.B_prefix = m_scdpoint->GetAttribute("prefix");
	//	if (m_scdpoint->GetChild("DOI") == DO_FAIL)
	//	{
	//		m_scdpoint->SwitchToIED();
	//	}
	//	m_scdpoint->SetRememberEle();
	//	m_scdpoint->analyzeDO(m_datalist_ex, strln, strlntype);
	//	m_scdpoint->switchRememberEle();
	//	while (m_scdpoint->GetNextChild("DOI") != DO_FAIL)
	//	{
	//		m_scdpoint->SetRememberEle();
	//		m_scdpoint->analyzeDO(m_datalist_ex, strln, strlntype);
	//		m_scdpoint->switchRememberEle();
	//	}
	//	m_scdpoint->SwitchToIED();

	//	ADDListToEx(m_lninst, m_datalist_ex, m_input);
	//	SwitchToInput();
    connect(ui->pushButton_fresh_ex, SIGNAL(clicked()), this, SLOT(onpushbutton_fresh_Sender()));

}

void InputDialog::OnDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	disconnect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

	int istartrow, istartcolumn, iendrow, iendcolumn;
	istartrow = topLeft.row();
	istartcolumn = topLeft.column();
	iendrow = bottomRight.row();
	iendcolumn = bottomRight.column();
	Input_Struct m_data;
	QString strap = ui->comboBox_localAP->currentText();
	QString strld = ui->comboBox_localLD->currentText();
	QString strln = tr("LLN0");
	int recode;
	recode = m_scdpoint->GetIEDByname(strcuried);
	recode = m_scdpoint->GetAccessPoint(strap);
	recode = m_scdpoint->GetLDnode(strld);
	recode = m_scdpoint->GetLNnode(strln);
	recode = m_scdpoint->GetChild("Inputs");

	if (Change_type == LOCAL_DATA)
	{
		for (int i = 0; i < m_olddatalist.size(); i++)
		{
			if (m_olddata.B_intAddr == m_olddatalist[i].B_intAddr)
			{
				m_data = m_olddatalist[i];
				m_data.B_intAddr = m_newdata.B_intAddr;
				m_data.B_intDesc = m_newdata.B_intDesc;
				break;
			}
		}
		recode = m_scdpoint->UpdataOneINPUT(m_olddata.B_intAddr, m_data, Change_type);
	}
	if (Change_type == EX_DATA)
	{
		m_newdata.B_intAddr = m_olddata.B_intAddr;
		recode = m_scdpoint->UpdataOneINPUT(m_olddata.B_intAddr, m_newdata, Change_type);
	}


	if (recode == DO_OK)
	{
		m_scdpoint->SwitchToIED();
		connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));
		return;
	}
	if (recode == DO_FAIL)
	{
		QMessageBox::about(0, tr("Alarm"), tr("Modify Value  false!,the name or datset must be not repeat"));
		m_scdpoint->SwitchToIED();
		connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

		return;
	}
	connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

}
void InputDialog::Combox_Local_LD_Active(QString str)
{
	Init_local_LN(str);
	m_scdpoint->SwitchToIED();
	ui->comboBox_localLN->setCurrentIndex(0);
	ui->comboBox_localLN->activated(ui->comboBox_localLN->currentText());
	Display_Input_Ln();
}


void InputDialog::Init_local_LD(QString str)
{
	int recode;
	m_scdpoint->GetIEDByname(strcuried);
	recode = m_scdpoint->GetAccessPoint(str);
	recode = m_scdpoint->GetChild("Server");
	recode = m_scdpoint->GetChild("LDevice");
	if (recode == DO_FAIL)
	{
		return;
	}
	QString str1;
	QStringList strlist;
	str1 = m_scdpoint->GetAttribute("inst");
	strlist.append(str1);
	while (m_scdpoint->GetNextChild("LDevice") == DO_OK)
	{
		str1 = m_scdpoint->GetAttribute("inst");
		strlist.append(str1);
	}
	ui->comboBox_localLD->clear();
	ui->comboBox_localLD->addItems(strlist);

}

void InputDialog::Init_local_LN(QString str)
{
	int recode;
	m_scdpoint->GetIEDByname(strcuried);
	recode = m_scdpoint->GetAccessPoint(ui->comboBox_localAP->currentText());
	recode = m_scdpoint->GetChild("Server");
	recode = m_scdpoint->GetChildByname_value("LDevice", "inst", str);
	if (recode == DO_FAIL)
	{
		return;
	}
	QString str1;
	QStringList strlist;
	recode = m_scdpoint->GetChild("LN0");
	str1 = m_scdpoint->GetAttribute("prefix") + m_scdpoint->GetAttribute("lnClass") + m_scdpoint->GetAttribute("inst");
	strlist.append(str1);
	while (m_scdpoint->GetNextChild("LN") == DO_OK)
	{
		str1 = m_scdpoint->GetAttribute("prefix") + m_scdpoint->GetAttribute("lnClass") + m_scdpoint->GetAttribute("inst");

		strlist.append(str1);
	}
	ui->comboBox_localLN->clear();
	ui->comboBox_localLN->addItems(strlist);

}

void InputDialog::Init_Ex_IED(QString str)
{
	int recode;
	QVector<IEDstruct> iedlist;
	recode = m_scdpoint->GetIEDList(iedlist);
	ui->comboBox_exIED->clear();
	for (int i = 0; i < iedlist.size(); i++)
	{
		if (iedlist[i].s_IEDname == strcuried)
		{
			continue;
		}
		ui->comboBox_exIED->addItem(iedlist[i].s_IEDname);
	}
	ui->comboBox_exIED->setCurrentIndex(-1);
}
void InputDialog::Init_Ex_AP(QString str)
{
	int recode;
	recode = m_scdpoint->GetIEDByname(str);
	if (recode == DO_FAIL)
	{
		return;
	}
	m_scdpoint->GetChild("AccessPoint");
	QString str1;
	QStringList strlist;
	strlist.clear();
	str1 = m_scdpoint->GetAttribute("name");
	strlist.append(str1);
	while (m_scdpoint->GetNextChild("AccessPoint") == DO_OK)
	{
		str1 = m_scdpoint->GetAttribute("name");
		strlist.append(str1);
	}
	m_scdpoint->SwitchRoot();
	ui->comboBox_exAP->clear();
	ui->comboBox_exAP->addItems(strlist);
	//    ui->comboBox_exAP->activated(0);
	//    ui->comboBox_exAP->activated(ui->comboBox_localAP->currentText());
}
void InputDialog::Init_Ex_LD(QString str)
{
	int recode;
	QString stried;
	stried = ui->comboBox_exIED->currentText();
	m_scdpoint->GetIEDByname(stried);
	recode = m_scdpoint->GetAccessPoint(str);
	recode = m_scdpoint->GetChild("Server");
	recode = m_scdpoint->GetChild("LDevice");
	if (recode == DO_FAIL)
	{
		return;
	}
	QString str1;
	QStringList strlist;
	str1 = m_scdpoint->GetAttribute("inst");
	strlist.append(str1);
	while (m_scdpoint->GetNextChild("LDevice") == DO_OK)
	{
		str1 = m_scdpoint->GetAttribute("inst");
		strlist.append(str1);
	}
	ui->comboBox_exLD->clear();
	ui->comboBox_exLD->addItems(strlist);

}

void InputDialog::Init_Ex_LN(QString str)
{
	int recode;
	QString stried;
	stried = ui->comboBox_exIED->currentText();
	m_scdpoint->GetIEDByname(stried);
	recode = m_scdpoint->GetAccessPoint(ui->comboBox_exAP->currentText());
	recode = m_scdpoint->GetChild("Server");
	recode = m_scdpoint->GetChildByname_value("LDevice", "inst", str);
	if (recode == DO_FAIL)
	{
		return;
	}
	QString str1;
	QStringList strlist;
	recode = m_scdpoint->GetChild("LN0");
	str1 = m_scdpoint->GetAttribute("prefix") + m_scdpoint->GetAttribute("lnClass") + m_scdpoint->GetAttribute("inst");
	strlist.append(str1);
	while (m_scdpoint->GetNextChild("LN") == DO_OK)
	{
		str1 = m_scdpoint->GetAttribute("prefix") + m_scdpoint->GetAttribute("lnClass") + m_scdpoint->GetAttribute("inst");

		strlist.append(str1);
	}
	ui->comboBox_exLN->clear();
	ui->comboBox_exLN->addItems(strlist);

}
void InputDialog::Combox_Ex_AP_Active(QString str)
{
	Init_Ex_LD(str);
	ui->comboBox_exLD->setCurrentIndex(0);
	ui->comboBox_exLD->activated(ui->comboBox_exLD->currentText());

}
void InputDialog::Combox_Ex_LD_Active(QString str)
{
	Init_Ex_LN(str);

}

void InputDialog::Combox_Ex_LN_Active(QString str)
{

}

void InputDialog::Combox_Ex_IED_Active(QString str)
{
	Init_Ex_AP(str);
	ui->comboBox_exAP->setCurrentIndex(0);
	ui->comboBox_exAP->activated(ui->comboBox_exAP->currentText());

}
void InputDialog::Combox_Local_LN_Active(QString str)
{

}

void InputDialog::Combox_Local_AP_Active(QString str)
{
	Init_local_LD(str);
	m_scdpoint->SwitchToIED();
	ui->comboBox_localLD->setCurrentIndex(0);
	ui->comboBox_localLD->activated(ui->comboBox_localLD->currentText());


}
void InputDialog::Display_Input_Ln()

{
	QString strap, strld, strln;
	strap = ui->comboBox_localAP->currentText();
	strld = ui->comboBox_localLD->currentText();
	m_ModelDate->setRowCount(0);
	//strln = ui->comboBox_localLN->;
	strln = tr("LLN0");
	int recode;

	//m_ModelDate->setRowCount(0);
	//recode = m_scdpoint->GetAccessPoint(strap);
	//recode = m_scdpoint->GetChild("Server");
	//if (m_scdpoint->GetChildByname_value("LDevice", "inst", strld) != DO_OK)
	//{
	//	m_scdpoint->SwitchToIED();
	//	return;
	//}
	//recode = m_scdpoint->GetLNnode(strln);
	recode = m_scdpoint->SwitchToNode(strcuried, strld, strln);
	recode = m_scdpoint->GetChild("Inputs");
	recode = m_scdpoint->GetChild("ExtRef");
	if (recode != DO_OK)
	{
		m_scdpoint->SwitchToIED();
		return;
	}
	//m_olddatalist.clear();
	Input_Struct m_data;
	GetInputFromSCD(&m_data);
	m_olddatalist.append(m_data);
	//m_SCDPoint->switchRememberEle();
	m_ModelDate->setRowCount(m_ModelDate->rowCount() + 1);

	AddOneInputToTable(m_ModelDate->rowCount() - 1, m_data);

	while (m_scdpoint->GetNextChild("ExtRef") == DO_OK)
	{
		Input_Struct m_data;
		//m_SCDPoint->SetRememberEle();
		GetInputFromSCD(&m_data);
		//m_olddatalist.append(m_data);
		//m_SCDPoint->switchRememberEle();
		m_ModelDate->setRowCount(m_ModelDate->rowCount() + 1);
		AddOneInputToTable(m_ModelDate->rowCount() - 1, m_data);

	}
	//m_scdpoint->SwitchToIED();
	m_scdpoint->SwitchRoot();
	return;
}
void InputDialog::GetInputFromSCD(Input_Struct* data)
{
	data->B_daName = m_scdpoint->GetAttribute("daName");
	data->B_doName = m_scdpoint->GetAttribute("doName");
	data->B_iedName = m_scdpoint->GetAttribute("iedName");
	data->B_intAddr = m_scdpoint->GetAttribute("intAddr");
	data->B_ldInst = m_scdpoint->GetAttribute("ldInst");
	data->B_lnClass = m_scdpoint->GetAttribute("lnClass");
	data->B_lnInst = m_scdpoint->GetAttribute("lnInst");
	data->B_prefix = m_scdpoint->GetAttribute("prefix");
	m_scdpoint->SetRememberEle();

	data->B_intDesc = m_scdpoint->GetSpecifytvalue(strcuried, data->B_intAddr, "desc");
	m_scdpoint->switchRememberEle();

	QString str;
	m_scdpoint->SetRememberEle();
	if (!data->B_iedName.isEmpty())
	{
		if (data->B_daName.isEmpty())
		{
			str = data->B_ldInst + "/" + data->B_prefix + data->B_lnClass + data->B_lnInst + "." + data->B_doName;
		}
		else
		{
			str = data->B_ldInst + "/" + data->B_prefix + data->B_lnClass + data->B_lnInst + "." + data->B_doName + "." + data->B_daName;

		}
		//data->B_exDesc = m_scdpoint->GetSpecifytvalue(data->B_iedName, str, "desc");
		data->B_exDesc = m_scdpoint->GetDescFromSpecifNode(data->B_iedName, data->B_ldInst, data->B_prefix + data->B_lnClass + data->B_lnInst, data->B_doName);
		//m_scdpoint->switchRememberEle();
	}



}


void InputDialog::AddOneInputToTable(int row, Input_Struct &data)
{
	disconnect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

	QString str;
	if (!data.B_daName.isEmpty())
	{
		str = data.B_ldInst + "/" + data.B_prefix+data.B_lnClass + data.B_lnInst + "." + data.B_doName + "." + data.B_daName;

	}
else
{
	str = data.B_ldInst + "/" + data.B_prefix + data.B_lnClass + data.B_lnInst + "." + data.B_doName;

}

	m_ModelDate->setData(m_ModelDate->index(row, 2), QVariant(data.B_iedName));
	m_ModelDate->setData(m_ModelDate->index(row, 3), QVariant(str));
	m_ModelDate->setData(m_ModelDate->index(row, 4), QVariant(data.B_exDesc));
	m_ModelDate->setData(m_ModelDate->index(row, 0), QVariant(data.B_intAddr));
	m_ModelDate->setData(m_ModelDate->index(row, 1), QVariant(data.B_intDesc));
	m_ModelDate->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ModelDate->item(row, 1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ModelDate->item(row, 2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ModelDate->item(row, 3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ModelDate->item(row, 4)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

}
void InputDialog::FreshInputOfTable(QModelIndex curIndex, QVector<Input_Struct> &datalist, int source)
{
	//m_olddatalist.clear();

	if (source == EX_DATA)    {
		int num;
		if (datalist.size() < (m_ModelDate->rowCount() - curIndex.row()))
		{
			num = datalist.size();
		}
		else
		{
			num = (m_ModelDate->rowCount() - curIndex.row());
		}
		for (int row = curIndex.row(), i = 0; i < num; row++, i++)
		{
			disconnect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

			Input_Struct m_data;


			m_data.B_intAddr = m_ModelDate->data(m_ModelDate->index(row, 0), Qt::EditRole).toString();

			//m_olddatalist.append(m_data);
			m_olddata = m_data;
			m_newdata = datalist[i];
			QString str;
			if (!datalist[i].B_iedName.isEmpty())
			{
				str = datalist[i].B_ldInst + "/" + datalist[i].B_prefix + datalist[i].B_lnClass + datalist[i].B_lnInst + "." + datalist[i].B_doName + "." + datalist[i].B_daName;

			}
			m_ModelDate->setData(m_ModelDate->index(row, 2), QVariant(datalist[i].B_iedName));
			m_ModelDate->setData(m_ModelDate->index(row, 3), QVariant(str));
			connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

			m_ModelDate->setData(m_ModelDate->index(row, 4), QVariant(datalist[i].B_exDesc));

		}

	}
	if (source == LOCAL_DATA)
	{
		int num;
		if (datalist.size() < (m_ModelDate->rowCount() - curIndex.row()))
		{
			num = datalist.size();
		}
		else
		{
			num = (m_ModelDate->rowCount() - curIndex.row());
		}
		for (int row = curIndex.row(), i = 0; i < num; row++, i++)
		{
			Input_Struct m_data;

			disconnect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

			m_data.B_intAddr = m_ModelDate->data(m_ModelDate->index(row, 0), Qt::EditRole).toString();

			//m_olddatalist.append(m_data);
			m_olddata = m_data;
			m_newdata = datalist[i];
			m_ModelDate->setData(m_ModelDate->index(row, 0), QVariant(datalist[i].B_intAddr));
			connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

			m_ModelDate->setData(m_ModelDate->index(row, 1), QVariant(datalist[i].B_intDesc));


		}


	}


}
void InputDialog::FreshInputOfTable(QModelIndex curIndex, QVector<FCDA_Struct> &datalist, int source)
{
	int num;
	Input_Struct m_input, m_olddata;
	if (datalist.size() < (m_ModelDate->rowCount() - curIndex.row()))
	{
		num = datalist.size();
	}
	else
	{
		num = (m_ModelDate->rowCount() - curIndex.row());
	}
	for (int i = 0; i < num; i++)
	{
		m_olddata.B_intAddr = m_ModelDate->data(m_ModelDate->index(curIndex.row() + i, 0), Qt::EditRole).toString();
		if (source == EX_DATA)
		{
			m_input.B_iedName = ui->comboBox_exIED->currentText();
			m_input.B_ldInst = datalist[i].B_ldInst;
			m_input.B_prefix = datalist[i].B_prefix;
			m_input.B_lnClass = datalist[i].B_lnClass;
			m_input.B_lnInst = datalist[i].B_lnInst;
			m_input.B_doName = datalist[i].B_doName;
			m_input.B_daName = datalist[i].B_daName;
		}
		else if (source == LOCAL_DATA)
		{
			m_input.B_intAddr = datalist[i].B_ldInst + "/" + datalist[i].B_prefix + datalist[i].B_lnClass + datalist[i].B_lnInst + "." + datalist[i].B_doName + "." + datalist[i].B_daName;
		}
		m_scdpoint->UpdataOneINPUT(strcuried, ui->comboBox_localLD->currentText(), "LLN0", m_olddata.B_intAddr, m_input, source);
	}
}

void InputDialog::ADDListToLocal(LN_InstStruct &Lninst, QVector<Data_instStruct> &Datalist)
{
	QTreeWidgetItem *firstClassItem;
	QString str_FC;
	QString LN_path;
	QStringList limt_list;
	QString strld;
	strld = ui->comboBox_localLD->currentText();
	str_FC = ui->comboBox_localFC->currentText();
	limt_list = ui->lineEdit_localDA->text().split("|");
	ui->treeWidget_local->clear();
	QTreeWidgetItem *IED_parent = ui->treeWidget_local->invisibleRootItem();

	LN_path = Lninst.B_ldinst + "/" + Lninst.B_prefix + Lninst.B_lnClass + Lninst.B_inst;
	firstClassItem = new QTreeWidgetItem(IED_parent);

	firstClassItem->setText(0, strld + LN_path);
	firstClassItem->setText(1, Lninst.B_desc);
	for (int i = 0; i < Datalist.size(); i++)
	{
		if ((str_FC == Datalist[i].B_FC) || (Datalist[i].B_FC == NULL))
		{
			if (limt_list.size() == 0)
			{
				QTreeWidgetItem *Item = new QTreeWidgetItem;
				Item->setText(0, strld + "/" + Datalist[i].B_Datalnst);
				Item->setText(1, Datalist[i].B_dU);
				firstClassItem->addChild(Item);

			}
			else
			{
				bool Limt_flag = false;
				for (int j = 0; j < limt_list.size(); j++)
				{
					if (Datalist[i].B_DA == NULL)
					{
						Limt_flag = false;
					}
					if (Datalist[i].B_DA.contains(limt_list[j]))
					{
						Limt_flag = true;
					}
				}
				if (Limt_flag == true)
				{
					QTreeWidgetItem *Item = new QTreeWidgetItem;
					Item->setText(0, strld + "/" + Datalist[i].B_Datalnst);
					Item->setText(1, Datalist[i].B_dU);
					firstClassItem->addChild(Item);

				}
			}

		}

	}

}
void InputDialog::ADDDatainstListTOTree(QVector<FCDA_Struct>&List)
{
	int i = 0;
	QTreeWidgetItem *firstClassItem;
	//QTreeWidgetItem *Item;// = new QTreeWidgetItem;
	QTreeWidgetItem *m_rootItem = ui->treeWidget_local->invisibleRootItem();
	while (i < List.size())
	{
		if (List[i].B_daName.isEmpty())
		{
			firstClassItem = new QTreeWidgetItem(m_rootItem);
			firstClassItem->setText(0, List[i].B_ldInst + "/" + List[i].B_prefix + List[i].B_lnClass + List[i].B_lnInst + "." + List[i].B_doName);
			firstClassItem->setText(1, List[i].B_DOdesc);
			i++;
			continue;
		}
		else
		{
			firstClassItem = new QTreeWidgetItem(m_rootItem);
			//Item = new QTreeWidgetItem;
			firstClassItem->setText(0, List[i].B_ldInst + "/" + List[i].B_prefix + List[i].B_lnClass + List[i].B_lnInst + "." + List[i].B_doName + "." + List[i].B_daName);
			if (List[i].B_dU.isEmpty())

			{
				firstClassItem->setText(1, List[i].B_DOdesc);
			}
			else
			{
				firstClassItem->setText(1, List[i].B_dU);
			}

			//firstClassItem->addChild(Item);
		}

		i++;
	}
}
void InputDialog::ADDListToEx(LN_InstStruct &Lninst, QVector<Data_instStruct> &Datalist, Input_Struct m_data)
{
	QTreeWidgetItem *firstClassItem;
	QString str_FC;
	QString LN_path;
	QStringList limt_list;
	QString doname, daname, str;
	int index;
	QString strld;
	m_newdatalist.clear();
	strld = ui->comboBox_exLD->currentText();
	str_FC = ui->comboBox_exFC->currentText();
	limt_list = ui->lineEdit_exDA->text().split("|");
	ui->treeWidget_ex->clear();
	QTreeWidgetItem *IED_parent = ui->treeWidget_ex->invisibleRootItem();
	IED_parent->takeChildren();
	LN_path = Lninst.B_ldinst + "/" + Lninst.B_prefix + Lninst.B_lnClass + Lninst.B_inst;
	firstClassItem = new QTreeWidgetItem(IED_parent);

	firstClassItem->setText(0, strld + LN_path);
	firstClassItem->setText(1, Lninst.B_desc);
	for (int i = 0; i < Datalist.size(); i++)
	{
		if ((str_FC == Datalist[i].B_FC) || (Datalist[i].B_FC == NULL))
		{
			if (limt_list.size() == 0)
			{

				QTreeWidgetItem *Item = new QTreeWidgetItem;
				Item->setText(0, strld + "/" + Datalist[i].B_Datalnst);
				Item->setText(1, Datalist[i].B_dU);
				firstClassItem->addChild(Item);
				Input_Struct _data = m_data;
				str = Datalist[i].B_Datalnst;
				index = str.indexOf(".");
				str = str.left(str.length() - index);
				str.remove(0, 1);
				index = str.indexOf(".");
				doname = str.right(index);
				daname = str.left(str.length() - index).remove(0, 1);
				_data.B_doName = doname;
				_data.B_daName = daname;
				_data.B_exDesc = Datalist[i].B_dU;
				m_newdatalist.append(_data);
			}
			else
			{
				bool Limt_flag = false;
				for (int j = 0; j < limt_list.size(); j++)
				{
					if (Datalist[i].B_DA == NULL)
					{
						Limt_flag = false;
					}
					if (Datalist[i].B_DA.contains(limt_list[j]))
					{
						Limt_flag = true;
					}
				}
				if (Limt_flag == true)
				{
					QTreeWidgetItem *Item = new QTreeWidgetItem;
					Item->setText(0, strld + "/" + Datalist[i].B_Datalnst);
					Item->setText(1, Datalist[i].B_dU);
					firstClassItem->addChild(Item);
					Input_Struct _data = m_data;
					str = Datalist[i].B_Datalnst;
					index = str.indexOf(".");
					str = str.right(str.length() - index);
					str.remove(0, 1);
					index = str.indexOf(".");
					doname = str.left(index);
					daname = str.right(str.length() - index).remove(0, 1);
					_data.B_doName = doname;
					_data.B_daName = daname;
					_data.B_exDesc = Datalist[i].B_dU;
					m_newdatalist.append(_data);
				}
			}

		}

	}

}
void InputDialog::ADDListToEx(DataSetStruct &m_data)
{
	QTreeWidgetItem *IED_parent = ui->treeWidget_ex->invisibleRootItem();
	QTreeWidgetItem*firstClassItem = new QTreeWidgetItem(IED_parent);
	QString strIED = ui->comboBox_exIED->currentText();
	QString strFC = ui->comboBox_exFC->currentText();
	firstClassItem->setText(0, m_data.DataSetName);
	firstClassItem->setText(1, m_data.DataSetDesc);

	for (int i = 0; i < m_data.FCDA_List.size(); i++)
	{
		QString data_Inst;
		if (m_data.FCDA_List[i].B_fc != strFC)
		{
			continue;
		}
		m_scdpoint->Filling_OneData(strIED, m_data.FCDA_List[i], m_data.Goose_state);
		QTreeWidgetItem *Item = new QTreeWidgetItem;
		data_Inst = m_data.FCDA_List[i].B_ldInst + "/" + m_data.FCDA_List[i].B_prefix + m_data.FCDA_List[i].B_lnClass + m_data.FCDA_List[i].B_lnInst + "." + m_data.FCDA_List[i].B_doName;
		if (!m_data.FCDA_List[i].B_daName.isEmpty())
		{
			data_Inst += "." + m_data.FCDA_List[i].B_daName;
		}

		Item->setText(0, data_Inst);
		Item->setText(1, m_data.FCDA_List[i].B_DOdesc);
		firstClassItem->addChild(Item);
	}
}
void InputDialog::SwitchToInput()
{
	QString strap, strld, strln;
	strap = ui->comboBox_localAP->currentText();
	strld = ui->comboBox_localLD->currentText();
	//strln = ui->comboBox_localLN->;
	strln = tr("LLN0");
	int recode;

	recode = m_scdpoint->GetAccessPoint(strap);
	recode = m_scdpoint->GetChild("Server");
	if (m_scdpoint->GetChildByname_value("LDevice", "inst", strld) != DO_OK)
	{
		m_scdpoint->SwitchToIED();
		return;
	}
	recode = m_scdpoint->GetLNnode(strln);
	recode = m_scdpoint->GetChild("Inputs");
	recode = m_scdpoint->GetChild("ExtRef");
	if (recode != DO_OK)
	{
		m_scdpoint->SwitchToIED();
		return;
	}
}
void InputDialog::itemDoubleClicked(QTreeWidgetItem *item, int colum)
{
	AddOneNewInput(item);
}
void InputDialog::AddOneNewInput(QTreeWidgetItem *item)
{
 	QTreeWidgetItem *root = ui->treeWidget_local->invisibleRootItem();
	int index = root->indexOfChild(item);
	FCDA_Struct m_data;
	m_data = DataInstList_Select_local.at(index);
	Input_Struct m_input;
	m_input.B_intAddr = m_data.B_ldInst + "/" + m_data.B_prefix + m_data.B_lnClass + m_data.B_lnInst + "." + m_data.B_doName + "." + m_data.B_daName;
	m_input.B_intDesc = m_data.B_DOdesc;
	int recode = m_scdpoint->CheckInputReceiver(strcuried, ui->comboBox_localAP->currentText(), ui->comboBox_localLD->currentText(), "LLN0", m_input);
	if (recode == DO_FAIL)
	{
		QMessageBox msgBox;
		msgBox.setText("The terminal is exist");
		msgBox.setInformativeText("The terminal only can be added once");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Ok)
		{
			return;
		}
	}
	m_scdpoint->AddOneINPUT(strcuried, ui->comboBox_localAP->currentText(), ui->comboBox_localLD->currentText(), ui->comboBox_localLN->currentText(), m_input);
	Display_Input_Ln();
	ui->dropTable->scrollToBottom();
	//QString intAddr, intdesc;
	//intAddr = item->text(0);
	//intdesc = item->text(1);
	//QString strap = ui->comboBox_localAP->currentText();
	//QString strld = ui->comboBox_localLD->currentText();
	//QString strln = tr("LLN0");
	//int recode;
	//recode = m_scdpoint->GetIEDByname(strcuried);
	//recode = m_scdpoint->GetAccessPoint(strap);
	//recode = m_scdpoint->GetLDnode(strld);
	//recode = m_scdpoint->GetLNnode(strln);
	//recode = m_scdpoint->GetChild("Inputs");
	//if (recode == DO_FAIL)
	//{

	//	recode = m_scdpoint->GetIEDByname(strcuried);
	//	recode = m_scdpoint->GetAccessPoint(strap);
	//	recode = m_scdpoint->GetLDnode(strld);
	//	recode = m_scdpoint->GetLNnode(strln);
	//	recode = m_scdpoint->CreatInputs();
	//	recode = m_scdpoint->GetChild("Inputs");
	//}
	//for (int i = 0; i < m_datalist_local.size(); i++)
	//{
	//	if (intAddr.contains(m_datalist_local[i].B_Datalnst))
	//	{
	//		disconnect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));


	//		Input_Struct m_data;
	//		m_data.B_intAddr = intAddr;
	//		m_data.B_intDesc = intdesc;
	//		//AddOneInputToTable(m_ModelDate->rowCount()-1,m_data);
	//		recode = m_scdpoint->CheckInputReceiver(m_data);
	//		if (recode == DO_FAIL)
	//		{
	//			QMessageBox msgBox;
	//			msgBox.setText("The terminal is exist");
	//			msgBox.setInformativeText("The terminal only can be added once");
	//			msgBox.setStandardButtons(QMessageBox::Ok);
	//			msgBox.setDefaultButton(QMessageBox::Ok);
	//			int ret = msgBox.exec();
	//			if (ret == QMessageBox::Ok)
	//			{
	//				return;
	//			}
	//		}
	//		m_ModelDate->setRowCount(m_ModelDate->rowCount() + 1);
	//		m_scdpoint->AddOneINPUT(m_data);
	//		Display_Input_Ln();
	//		connect(m_ModelDate, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnDataChanged(const QModelIndex &, const QModelIndex &)));

	//		return;
	//	}
	//}
}
int InputDialog::Filter_datainst(FCDA_Struct &m_data)
{
	QString str1, str2;
	if (m_data.B_daName.isEmpty())
	{
		return DO_OK;
	}
	str1 = m_data.B_doName + m_data.B_daName;
	str1.remove(".");
	for (int i = 0; i < DataMatrix_Vector_LN_Local.size(); i++)
	{
		str2 = DataMatrix_Vector_LN_Local[i].B_doName + DataMatrix_Vector_LN_Local[i].B_daName;
		str2.remove(".");
		if (m_data.B_LNodeType == DataMatrix_Vector_LN_Local[i].B_LNodeType)
		{
			if (str1 == str2)
			{
				m_data.B_doName.clear();
				m_data.B_daName.clear();
				m_data.B_doName += DataMatrix_Vector_LN_Local[i].B_doName;
				m_data.B_daName += DataMatrix_Vector_LN_Local[i].B_daName;
				m_data.B_fc += DataMatrix_Vector_LN_Local[i].B_Fc;
				return DO_OK;
			}
		}

	}
}
void InputDialog::DropTable_MousEvent(const QPoint &pos)
{
	actionDel->setEnabled(true);
	if (m_ModelDate->rowCount() == 0)
	{

		actionDel->setEnabled(false);

	}
	m_ModelSlection = ui->dropTable->selectionModel();
	QModelIndexList indexes;

	indexes.clear();
	indexes = m_ModelSlection->selectedIndexes();

	if (indexes.size() == 0)
	{
		actionDel->setEnabled(false);
	}

	m_Menu->exec(QCursor::pos());
}
void InputDialog::OnAction_Del()
{
	m_ModelSlection = ui->dropTable->selectionModel();
	QModelIndexList indexes;
	QModelIndex index;
	indexes.clear();
	indexes = m_ModelSlection->selectedIndexes();
	QString Ld = ui->comboBox_localLD->currentText();
	if (indexes.size() == 0)
	{
		actionDel->setEnabled(false);
	}
	foreach(index, indexes)
	{
		QString str = m_ModelDate->data(m_ModelDate->index(index.row(), 0)).toString();
		m_scdpoint->DelOneINPUT(strcuried, Ld, "LLN", str);
	}
	Display_Input_Ln();
}

﻿#include"mainwindow.h"
#include"ui_mainwindow.h"
void MainWindow::Init_GSE()
{



	headerList.clear();
	headerList << tr("name") << tr("datset") << tr("confRev") << tr("type") << tr("appID") << tr("desc");


	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	m_ModelIED_GSE->clear();

	ClearTableDelegate(headerList.size());
	disconnect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));
	m_ModelIED_GSE->setColumnCount(headerList.count());

	ui->tableView->setModel(m_ModelIED_GSE);
	for (int i = 0; i < headerList.count(); i++)
	{
		m_ModelIED_GSE->setHeaderData(i, Qt::Horizontal, headerList.at(i));
		ui->tableView->setItemDelegateForColumn(i, ui->tableView->itemDelegateForColumn(0));
		ui->tableView->setColumnWidth(i, 150);
	}
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

	connect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));

}
void MainWindow::OnGSEDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	disconnect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));

	int istartrow, istartcolumn, iendrow, iendcolumn;
	istartrow = topLeft.row();
	istartcolumn = topLeft.column();
	iendrow = bottomRight.row();
	iendcolumn = bottomRight.column();
	GSE_InstStruct m_data;
	QString str = ui->comboBox_LD->currentText();
	QStringList strlist;
	strlist = str.split(":");
	QString strap, strld, strln;
	strap = strlist[0];
	strld = strlist[1];
	strln = ui->comboBox_LN->currentText();
	int recode;
	GetGSEBLKFromTable(istartrow, m_data);
	if (istartcolumn == 2)
	{
		m_data.B_confRev = "1.0";
	}
	str = m_data.B_datSet;
	str.replace("ds", "gs", Qt::CaseInsensitive);
	m_data.B_name = str;
	recode = m_SCDPoint->UpdataOneGSEBLK(strIEDname, strld, strln, m_data, strGsename);
	if (recode==DO_OK)
	{
		if (strGsename != m_data.B_name)
		{
			recode = m_SCDPoint->UpdataConnectAPByGOOSE(strIEDname, strap, strld, strGsename, m_data);

		}
	}


	if (recode == DO_OK)
	{
		Reversion_Flag = 1;
		Change_Flag = 1;
		m_SCDPoint->SwitchToIED();
		connect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));
		ui->comboBox_LD->activated(ui->comboBox_LD->currentText());

		return;
	}
	if (recode == DO_FAIL)
	{
		QMessageBox::about(0, tr("Alarm"), tr("Modify Value  false!,the name or datset must be not repeat"));
		m_SCDPoint->SwitchToIED();
		ui->comboBox_LD->activated(ui->comboBox_LD->currentText());
		return;
	}
	connect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));

}
void MainWindow::DisplayGSE()
{
	disconnect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));
	QString str = ui->comboBox_LD->currentText();
	QStringList strlist;
	strlist = str.split(":");
	QString strap, strld, strln;
	strap = strlist[0];
	strld = strlist[1];
	QVector<GSE_InstStruct>List;
	strln = ui->comboBox_LN->currentText();
	int recode;
	datasetlist.clear();

	GOOSETypeCombox *gooseCombox = new GOOSETypeCombox(this);
	ui->tableView->setItemDelegateForColumn(3, gooseCombox);
	m_ModelIED_GSE->setRowCount(0);
	datasetlist.clear();
	m_SCDPoint->GetDataSetList(strIEDname, strld, strln, datasetlist);
	int index = 0;
	while (index < datasetlist.size())
	{
		if (!datasetlist.at(index).contains("goose", Qt::CaseInsensitive))
		{

			datasetlist.removeAt(index);
			index = 0;
		}
		else
		{
			index++;
		}
	}
	DataSetListCombox *DataSetCombox = new DataSetListCombox(this);


	ui->tableView->setItemDelegateForColumn(1, DataSetCombox);


	DataSetCombox->DatasetList = datasetlist;
	recode = m_SCDPoint->GetGSEList(strIEDname, strld, strln, List);
	for (int i = 0; i < List.size(); i++)
	{
		m_ModelIED_GSE->setRowCount(i + 1);
		AddOneGSEToTable(i, List[i]);
	}
	//    while (m_SCDPoint->GetNextChild("DataSet") == DO_OK)
	//    {
	//    datasetlist.append(m_SCDPoint->GetAttribute("name"));

	//    }
	//    m_SCDPoint->SwitchParent();
	//    DataSetListCombox *DataSetCombox= new DataSetListCombox(this);
	//    DataSetCombox->DatasetList = datasetlist;
	//    ui->tableView->setItemDelegateForColumn(1,DataSetCombox);



	//    recode = m_SCDPoint->GetChild("GSEControl");
	//    if(recode!=DO_OK)
	//    {
	//		m_SCDPoint->SwitchToIED();
	//        connect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));
	//        return;
	//    }
	//	m_ModelIED_GSE->setRowCount(m_ModelIED_GSE->rowCount() + 1);

	//    AddOneGSEToTable(m_ModelIED_GSE->rowCount() - 1);

	//    while (m_SCDPoint->GetNextChild("GSEControl") == DO_OK)
	//    {
	//		m_ModelIED_GSE->setRowCount(m_ModelIED_GSE->rowCount() + 1);
	//		AddOneGSEToTable(m_ModelIED_GSE->rowCount() - 1);

	//    }
	//    m_SCDPoint->SwitchToIED();
	connect(m_ModelIED_GSE, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnGSEDataChanged(const QModelIndex &, const QModelIndex &)));

	return;

}
void MainWindow::AddOneGSEToTable(int row)
{
	QString strvalue;
	strvalue = m_SCDPoint->GetAttribute("name");
	strvalue = m_SCDPoint->GetAttribute("datSet");
	strvalue = m_SCDPoint->GetAttribute("confRev");
	strvalue = m_SCDPoint->GetAttribute("type");
	strvalue = m_SCDPoint->GetAttribute("appID");
	strvalue = m_SCDPoint->GetAttribute("desc");
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 0), QVariant(m_SCDPoint->GetAttribute("name")));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 1), QVariant(m_SCDPoint->GetAttribute("datSet")));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 2), QVariant(m_SCDPoint->GetAttribute("confRev")));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 3), QVariant(m_SCDPoint->GetAttribute("type")));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 4), QVariant(m_SCDPoint->GetAttribute("appID")));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 5), QVariant(m_SCDPoint->GetAttribute("desc")));
	m_ModelIED_GSE->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ModelIED_GSE->item(row, 4)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	//m_ModelIED_GSE->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}
void MainWindow::AddOneGSEToTable(int row, GSE_InstStruct &data)
{
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 0), QVariant(data.B_name));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 1), QVariant(data.B_datSet));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 2), QVariant(data.B_confRev));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 3), QVariant(data.B_type));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 4), QVariant(data.B_appID));
	m_ModelIED_GSE->setData(m_ModelIED_GSE->index(row, 5), QVariant(data.B_desc));
	m_ModelIED_GSE->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	m_ModelIED_GSE->item(row, 4)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void MainWindow::AddOneGSECTRL()
{
	QString str = ui->comboBox_LD->currentText();
	QStringList strlist;
	strlist = str.split(":");
	QString strap, strld, strln;
	strap = strlist[0];
	strld = strlist[1];
	strln = ui->comboBox_LN->currentText();
	GSE_InstStruct m_Data;
	int recode = m_SCDPoint->AddOneGSECtrl(strIEDname, strld, strln, datasetlist, m_Data);

	if (recode == DO_OK)
	{
		recode = m_SCDPoint->AddConnectAPByGOOSE(strIEDname, strap, strld, m_Data);

	}
	//GetGSEBLKFromTable(m_ModelIED_GSE->rowCount() - 1, m_Data);
	if (recode == DO_OK)
	{
		Reversion_Flag = 1;

	}
	ui->comboBox_LD->activated(ui->comboBox_LD->currentText());

}
void MainWindow::DelOneGSECTRL()
{
	QModelIndex index;
	QModelIndexList indexes;
	QString str = ui->comboBox_LD->currentText();
	QStringList strlist;
	strlist = str.split(":");
	QString strap, strld, strln;
	strap = strlist[0];
	strld = strlist[1];
	strln = ui->comboBox_LN->currentText();
	m_ModelSlection = ui->tableView->selectionModel();
	indexes.clear();
	indexes = m_ModelSlection->selectedRows();
	if (indexes.size() == 0)
	{
		ui->comboBox_LD->activated(ui->comboBox_LD->currentText());
		return;
	}
	foreach(index, indexes)
	{
		GSE_InstStruct m_Data;
		str = m_ModelIED_GSE->data(m_ModelIED_GSE->index(index.row(), 0)).toString();
		GetGSEBLKFromTable(index.row(), m_Data);
		m_SCDPoint->DelOneGSEBlK(strIEDname, strld, strln, str);
		m_SCDPoint->DelConnectAPByGOOSE(strIEDname, strap, strld, m_Data);


	}
	Reversion_Flag = 1;
	ui->comboBox_LD->activated(ui->comboBox_LD->currentText());
}
void MainWindow::OnGSECtrlClicked(const QModelIndex & index)
{
	strGsename = m_ModelIED_GSE->data(m_ModelIED_GSE->index(index.row(), 0)).toString();

}
void MainWindow::GetGSEBLKFromTable(int row, GSE_InstStruct &data)
{
	data.B_name = m_ModelIED_GSE->data(m_ModelIED_GSE->index(row, 0), Qt::EditRole).toString();
	data.B_datSet = m_ModelIED_GSE->data(m_ModelIED_GSE->index(row, 1), Qt::EditRole).toString();
	data.B_confRev = m_ModelIED_GSE->data(m_ModelIED_GSE->index(row, 2), Qt::EditRole).toString();
	data.B_type = m_ModelIED_GSE->data(m_ModelIED_GSE->index(row, 3), Qt::EditRole).toString();
	data.B_appID = m_ModelIED_GSE->data(m_ModelIED_GSE->index(row, 4), Qt::EditRole).toString();
//	if (!strGsename.isEmpty())
//	{
//		data.B_appID.replace(strGsename, data.B_name);
//	}

	data.B_desc = m_ModelIED_GSE->data(m_ModelIED_GSE->index(row, 5), Qt::EditRole).toString();
}

﻿#include"mainwindow.h"
#include"ui_mainwindow.h"
void MainWindow::Get_IEDList(QString str)
{
	//m_SCDPoint->GetIEDList(IedList);
	for (int i = 0; i < IedList.size(); i++)
	{

		AddoneItemToTree(IedList[i].s_IEDname, str);

	}

}
void MainWindow::ImportOneCID()
{
    ui->textBrowser->clear();
	int state = Import_OneIED(1);
	if (state == DO_OK)
	{
        Version_Flag=1;
	}
	else if (state == DO_FAIL)
	{
		QMessageBox::about(0, tr("Alarm"), tr("Import CID false!"));
	}

	//ui->tableView->clear();
	
    ui->SCLTree->clear();
    InitSCDtree();
	SCLTree_IEDNODE_DoubleClick("IEDNODE");


}
void MainWindow::ImportOneICD()
{
    ui->textBrowser->clear();
	int state = Import_OneIED(2);
	if (state == DO_OK)
	{
        Version_Flag=1;
	}
	else if (state == DO_FAIL)
	{
		QMessageBox::about(0, tr("Alarm"), tr("Import ICD false!"));
	}

	//ui->tableView->clear();

	ui->SCLTree->clear();
	InitSCDtree();
	SCLTree_IEDNODE_DoubleClick("IEDNODE");


}
int MainWindow::Import_OneIED(int state)
{
	QString strfilename;
	QString striedname;
	int irecode;
	ImportOneIed * m_importIED = new ImportOneIed(this, m_SCDPoint);

	m_importIED->setState(state);
	m_importIED->InitDlg();
	if (m_importIED->exec() == QDialog::Accepted)
	{
		strfilename = m_importIED->GetFileName();
		striedname = m_importIED->GetIEDName();
		if (strfilename.contains(".CID", Qt::CaseInsensitive))
		{
            irecode = m_SCDPoint->ImportCID(strfilename, striedname);
			//QMessageBox::about(0, tr("Alarm"), QString::number(irecode));
			return irecode;
		}
		else if (strfilename.contains(".ICD", Qt::CaseInsensitive))
		{
			irecode = m_SCDPoint->ImportICD(strfilename, striedname);
			return irecode;

		}
	}
	else
	{
		return DO_OD;
	}
	return DO_FAIL;

}
void MainWindow::DisplayIEDnode(QString str)
{

	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

	
	m_ModelIEDNode->setRowCount(0);

	disconnect(m_ModelIEDNode, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnIEDDataChanged(const QModelIndex &, const QModelIndex &)));

	for (int i = 0; i<IedList.size(); i++)
	{
		m_ModelIEDNode->setRowCount(m_ModelIEDNode->rowCount() + 1);
		AddOneIEDToTable(i, IedList[i]);

	}
	connect(m_ModelIEDNode, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnIEDDataChanged(const QModelIndex &, const QModelIndex &)));

}
void MainWindow::AddOneIEDToTable(int row, IEDstruct Item)
{
	m_ModelIEDNode->setData(m_ModelIEDNode->index(row, 0), QVariant(Item.s_IEDname));
	m_ModelIEDNode->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ModelIEDNode->setData(m_ModelIEDNode->index(row, 1), QVariant(Item.s_IEDtype));
	m_ModelIEDNode->item(row, 1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	m_ModelIEDNode->setData(m_ModelIEDNode->index(row, 2), QVariant(Item.s_IEDvendor));
	m_ModelIEDNode->item(row, 2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	m_ModelIEDNode->setData(m_ModelIEDNode->index(row, 3), QVariant(Item.s_IEDversion));
	m_ModelIEDNode->item(row, 3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	m_ModelIEDNode->setData(m_ModelIEDNode->index(row, 4), QVariant(Item.s_IEDdesc));
}
void MainWindow::OnIEDDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	int istartrow, istartcolumn, iendrow, iendcolumn;
	istartrow = topLeft.row();
	istartcolumn = topLeft.column();
	iendrow = bottomRight.row();
	iendcolumn = bottomRight.column();
	QString str1,IEDname;
	//str1 = headerList[istartcolumn];
	if (istartcolumn == 0)
	{
		str1 = "name";
	}
	else if (istartcolumn == 1)
	{
		str1 = "type";
	}
	else if (istartcolumn == 2)
	{
		str1 = "manufacturer";
	}
	else if (istartcolumn == 3)
	{
		str1 = "configVersion";
	}
	else if (istartcolumn == 4)
	{
		str1 = "desc";
	}
	IEDname = m_ModelIEDNode->data(m_ModelIEDNode->index(istartrow, 0), Qt::EditRole).toString();
	QString str2 = m_ModelIEDNode->data(topLeft, Qt::EditRole).toString();
	CurrentItem->child(istartrow)->setText(0, str2);
	ui->tableView->selectionModel()->clear();
	int recode;
	recode = m_SCDPoint->UpdataIEDAttribute(IEDname, str1, str2);
	if (recode == DO_OK)
	{

        Change_Flag = 1;
        Reversion_Flag=1;
		Get_Node("IEDNODE");
		CurrentItem->takeChildren();
		Get_IEDList("IED");
		DisplayIEDnode("IEDNODE");


	}
	if (recode == DO_FAIL)
	{
		QMessageBox::about(0, tr("Alarm"), tr("Modify Value  false!"));
	}

}

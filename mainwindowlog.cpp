﻿#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"datastruct.h"
#include"rptchange.h"
void MainWindow::Init_Log()
{
    headerList.clear();
    headerList << tr("name")  << tr("datSet") << tr("logName")<< tr("intgPd") << tr("logEna") << tr("reasonCode")<< tr("TrgOps") <<tr("desc");
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView->setAcceptDrops(true);
    m_ModelIED_Log->clear();
	ClearTableDelegate(headerList.size());

    disconnect(m_ModelIED_Log, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnLogDataChanged(const QModelIndex &, const QModelIndex &)));
    m_ModelIED_Log->setColumnCount(headerList.count());

    ui->tableView->setModel(m_ModelIED_Log);
    for (int i = 0; i < headerList.count(); i++)
    {
        m_ModelIED_Log->setHeaderData(i, Qt::Horizontal, headerList.at(i));
    }
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    connect(m_ModelIED_Log, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnLogDataChanged(const QModelIndex &, const QModelIndex &)));


}
void MainWindow::OnLogDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    disconnect(m_ModelIED_Log, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnLogDataChanged(const QModelIndex &, const QModelIndex &)));

    int istartrow, istartcolumn, iendrow, iendcolumn;
    istartrow = topLeft.row();
    istartcolumn = topLeft.column();
    iendrow = bottomRight.row();
    iendcolumn = bottomRight.column();
    LOG_CTRLStruct m_data;
    QString str = ui->comboBox_LD->currentText();
    QStringList strlist;
    strlist = str.split(":");
    QString strap, strld, strln;
    strap = strlist[0];
    strld = strlist[1];
    strln = ui->comboBox_LN->currentText();
    int recode;
    GetLOGFromTable(istartrow,m_data);
	bool b = m_data.B_name.contains(QRegExp("[\\x4e00-\\x9fa5]+"));
	if (b)
	{
		QMessageBox::about(0, tr("Alarm"), tr("the name of  log control block only can be characters and numbers "));
		ui->comboBox_LD->activated(ui->comboBox_LD->currentText());
		return;
	}

    recode =m_SCDPoint->UpdataOneLOGBLK(strIEDname,strld,strln,m_data,strLOGname);
    if (recode == DO_OK)
    {
        Change_Flag = 1;
        Reversion_Flag=1;
        connect(m_ModelIED_Log, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnLogDataChanged(const QModelIndex &, const QModelIndex &)));
        ui->comboBox_LD->activated(ui->comboBox_LD->currentText());
        return;
    }
    if (recode == DO_FAIL)
    {
        QMessageBox::about(0, tr("Alarm"), tr("Modify Value  false!,the name or datset must be not repeat"));
        ui->comboBox_LD->activated(ui->comboBox_LD->currentText());
        return;
    }

}
void MainWindow::DisplayLOG()
{
    disconnect(m_ModelIED_Log, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnLogDataChanged(const QModelIndex &, const QModelIndex &)));
    QString str = ui->comboBox_LD->currentText();
    QStringList strlist;
    strlist = str.split(":");
    QString strap, strld,strln;
    QVector<LOG_CTRLStruct> List;
    strap = strlist[0];
    strld = strlist[1];
    strln =ui->comboBox_LN->currentText();
    int recode;
    datasetlist.clear();
    m_SCDPoint->GetDataSetList(strIEDname,strld,strln,datasetlist);
	int i = 0;
	while (i < datasetlist.size())
	{
		if (!datasetlist.at(i).contains("log", Qt::CaseInsensitive) )
		{
			datasetlist.removeAt(i);
			i = 0;

		}
		else
		{
			i++;
		}
	}
    BOOLTypeCombox *BoolCombox = new BOOLTypeCombox(this);
    ui->tableView->setItemDelegateForColumn(4, BoolCombox);
    ui->tableView->setItemDelegateForColumn(5, BoolCombox);
    ListCombox *listcombox = new ListCombox(this);
    listcombox->list = datasetlist;
    ui->tableView->setItemDelegateForColumn(1, listcombox);
    m_ModelIED_Log->setRowCount(0);
    recode =m_SCDPoint->GetLOGList(strIEDname,strld,strln,List);
    for(int i =0;i<List.size();i++)
    {
        m_ModelIED_Log->setRowCount(i+1);
        AddOneLOGToTable(i,List[i]);
    }


    connect(m_ModelIED_Log, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(OnLogDataChanged(const QModelIndex &, const QModelIndex &)));

    return;

}
void MainWindow::AddOneLOGToTable(int row,LOG_CTRLStruct &data)
{
    QString strvalue;
    strvalue.clear();
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 0), QVariant(data.B_name));
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 1), QVariant(data.B_datSet));
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 2), QVariant(data.B_logName));
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 3), QVariant(data.B_intgPd));
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 4), QVariant(data.B_logEna));
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 5), QVariant(data.B_reasonCode));
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 7), QVariant(data.B_desc));
    strvalue="dchg="+data.m_Trgops.B_dchg+",dupd="+data.m_Trgops.B_dupd+",period="+data.m_Trgops.B_period+",qchg="+data.m_Trgops.B_qchg;
    m_ModelIED_Log->setData(m_ModelIED_Log->index(row, 6), QVariant(strvalue));

}
void MainWindow::GetLOGFromSCD(LOG_CTRLStruct* data)
{
   data->B_name = m_SCDPoint->GetAttribute("name");
   data->B_datSet = m_SCDPoint->GetAttribute("datSet");
   data->B_intgPd = m_SCDPoint->GetAttribute("intgPd");
   data->B_logName = m_SCDPoint->GetAttribute("logName");
   data->B_logEna = m_SCDPoint->GetAttribute("logEna");
   data->B_reasonCode = m_SCDPoint->GetAttribute("reasonCode");
   data->B_desc = m_SCDPoint->GetAttribute("desc");
   m_SCDPoint->GetChild("TrgOps");
   data->m_Trgops.B_dchg = m_SCDPoint->GetAttribute("dchg");
   data->m_Trgops.B_dupd = m_SCDPoint->GetAttribute("dupd");
   data->m_Trgops.B_period = m_SCDPoint->GetAttribute("period");
   data->m_Trgops.B_qchg = m_SCDPoint->GetAttribute("qchg");
   m_SCDPoint->SwitchParent();
}
void MainWindow::OnLOGCtrlClicked(const QModelIndex & index)
{
   strLOGname = m_ModelIED_Log->data(m_ModelIED_Log->index(index.row(), 0)).toString();

}
void MainWindow::GetLOGFromTable(int row,LOG_CTRLStruct  &data)
{
    QStringList strlist;
    QString str;
    data.B_name = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 0), Qt::EditRole).toString();
    data.B_datSet = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 1), Qt::EditRole).toString();

    data.B_logName = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 2), Qt::EditRole).toString();

    data.B_intgPd = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 3), Qt::EditRole).toString();

    data.B_logEna = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 4), Qt::EditRole).toString();
    data.B_reasonCode = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 5), Qt::EditRole).toString();
    data.B_desc = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 7), Qt::EditRole).toString();

    str = m_ModelIED_Log->data(m_ModelIED_Log->index(row, 6), Qt::EditRole).toString();
    strlist = str.split(",");
    for(int i =0;i<strlist.size();i++)
    {
        str = strlist.at(i);
        if(str.contains("dchg"))
        {
            if(str.contains("true"))
            {
                data.m_Trgops.B_dchg = "true";
            }else
            {
                data.m_Trgops.B_dchg = "false";
            }
        }
        if (str.contains("dupd"))
        {
            if(str.contains("true"))
            {
                data.m_Trgops.B_dupd = "true";
            }else
            {
                data.m_Trgops.B_dupd = "false";
            }
        }
        if (str.contains("period"))
        {
            if(str.contains("true"))
            {
                data.m_Trgops.B_period = "true";
            }else
            {
                data.m_Trgops.B_period = "false";
            }
        }
        if (str.contains("qchg"))
        {
            if(str.contains("true"))
            {
                data.m_Trgops.B_qchg = "true";
            }else
            {
                data.m_Trgops.B_qchg = "false";
            }
        }
    }

}
void MainWindow::OnLOGCtrldoubleClicked(const QModelIndex & index)
{
    LOG_CTRLStruct m_data;
    GetLOGFromTable(index.row(), m_data);
    if(index.column()==6)
    {

       RptChange *m_dlg = new RptChange(this);
       m_dlg->istate =1;
       m_dlg->m_Trgops = m_data.m_Trgops;
       m_dlg->init_dlg();
       m_dlg->Displaydata();
       if (m_dlg->exec()==QDialog::Accepted)
       {
           m_data.m_Trgops = m_dlg->m_Trgops;
               AddOneLOGToTable(index.row(),m_data);
       }
       else
       {
        return;
       }
    }



}

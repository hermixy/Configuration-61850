﻿#include"mainwindow.h"
#include"ui_mainwindow.h"
void MainWindow::AddOneSubNet()
{
    //QTreeWidgetItem *Item =new QTreeWidgetItem;
    QString str;
    str = m_SCDPoint->CreatOneSubNet();
	if (str.isEmpty())
	{
		return;
	}
    //Item->setText(0, str);
    Get_Node(CurrentTitle);
    //CurrentItem->addChild(Item);
    CurrentItem->takeChildren();
	Get_Communication("Communication");
    Get_CommunicationList("Communication");
    DisplayCommunication("Communication");
}
void MainWindow::DelOneSubNet(QModelIndex index,QString strname)
{
    //QTreeWidgetItem *Item =CurrentItem->child(index.row());
    //QString str;
    int recode;
    //Item->setText(0, strname);
    recode=m_SCDPoint->DeleteOneSubNet(strname);
    //CurrentItem->removeChild(Item);
    Get_Node(CurrentTitle);
    CurrentItem->takeChildren();
	Get_Communication("Communication");
    Get_CommunicationList("Communication");
    DisplayCommunication("Communication");
}
void MainWindow::Get_CommunicationList(QString str)
{
    
    for(int i =0;i<CommItemList.size();i++)
    {

        AddoneItemToTree(CommItemList[i].s_SubNet_name,str);

    }

}

void MainWindow::DisplayCommunication(QString str)
{

		//ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        
        m_ModelCommunication->setRowCount(0);
        disconnect(m_ModelCommunication,SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &)),this,SLOT(OnCommDataChanged(const QModelIndex &,const QModelIndex &)));

        for(int i =0;i<CommItemList.size();i++)
        {
            m_ModelCommunication->setRowCount(m_ModelCommunication->rowCount()+1);
            AddOneSubnetToTable(i,CommItemList[i]);

        }
        connect(m_ModelCommunication,SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &)),this,SLOT(OnCommDataChanged(const QModelIndex &,const QModelIndex &)));

}
void MainWindow::Get_Communication(QString str)
{
    int recordcount = m_SCDPoint->GetChildNum();
    CommItemList.clear();
	//const char *chr;
    for(int i=0;i<recordcount;i++)
    {
		CommItem m_CommItem;
		//m_Element = CurElement;
		//std::string str = value.toStdString();

		//const char* ch = str.c_str();
		m_CommItem.s_SubNet_desc = m_SCDPoint->GetAttribute(i, "desc");
		//chr = m_SCDPoint->GetAttribute(i, "name");
		m_CommItem.s_SubNet_name = m_SCDPoint->GetAttribute(i, "name");
        m_CommItem.s_SubNet_type = m_SCDPoint->GetAttribute(i,"type");

        CommItemList.append(m_CommItem);
    }
}
void MainWindow::AddOneSubnetToTable(int row, CommItem Item)
{
    m_ModelCommunication->setData(m_ModelCommunication->index(row,0),QVariant(Item.s_SubNet_name));
    m_ModelCommunication->setData(m_ModelCommunication->index(row,1),QVariant(Item.s_SubNet_type));
    m_ModelCommunication->setData(m_ModelCommunication->index(row,2),QVariant(Item.s_SubNet_desc));
	m_ModelCommunication->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ModelCommunication->item(row, 1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


}
void MainWindow::OnCommDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    int istartrow,istartcolumn,iendrow,iendcolumn;
    istartrow=topLeft.row();
    istartcolumn=topLeft.column();
    iendrow=bottomRight.row();
    iendcolumn=bottomRight.column();
    QString str1;
    str1 = m_ModelCommunication->data(m_ModelCommunication->index(topLeft.row(),0)).toString();
	QString str2 = m_ModelCommunication->data(topLeft, Qt::EditRole).toString();


    int recode;
	recode = m_SCDPoint->UpdateCommunicationAttribute(str1,"desc", str2);
	if (recode==DO_OK)
	{
        Reversion_Flag=1;
        Change_Flag = 1;
		CurrentItem->takeChildren();
		Get_Communication("Communication");
		Get_CommunicationList("Communication");
		ui->tableView->selectionModel()->clear();
		
	}
    if(recode==DO_FAIL)
    {
        QMessageBox::about(0,tr("Alarm"),tr("Modify Value  false!"));
    }

}
void MainWindow::OnSubnetDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    Change_Flag = 1;
	Reversion_Flag = 1;
}

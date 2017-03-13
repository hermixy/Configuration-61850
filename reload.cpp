﻿#include "reload.h"
#include "ui_reload.h"

ReLoad::ReLoad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReLoad)
{
    ui->setupUi(this);
    Model = new QStandardItemModel;
    //ModelSlection=new QItemSelectionModel;
    setWindowTitle(tr("Chose IED"));
    connect(ui->pushButton_apply, SIGNAL(clicked()), this, SLOT(Pushbutton_apply()));

    connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(Pushbutton_cancel()));

}

ReLoad::~ReLoad()
{
    delete ui;
}
void ReLoad::Init_dlg()
{

    ui->pushButton_apply->setText(tr("Apply"));
    ui->pushButton_cancel->setText(tr("Cancel"));
    QStringList Interactive;
    Interactive<<tr("IED Name");
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    Model->clear();
    Model->setColumnCount(Interactive.count());
    ui->tableView->setModel(Model);
    for (int i = 0; i < Interactive.count(); i++)
    {
        Model->setHeaderData(i, Qt::Horizontal, Interactive.at(i));

    }
}

void ReLoad::Display()
{
   for(int i = 0;i<IEDList.size();i++)
   {
    Model->setRowCount(i+1);
    Model->setData(Model->index(i,0),QVariant(IEDList[i]));
	Model->item(i, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

   }

}

void ReLoad::Pushbutton_apply()
{
    ModelSlection = ui->tableView->selectionModel();
    QModelIndexList indexes;
    QModelIndex index;
    indexes.clear();
    indexes = ModelSlection->selectedIndexes();
    foreach (index, indexes)
    {
        IED_select = Model->data(index).toString();
    }
    accept();
}

void ReLoad::Pushbutton_cancel()
{
reject();
}

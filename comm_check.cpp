﻿#include "comm_check.h"
#include "ui_comm_check.h"

Comm_check::Comm_check(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Comm_check)
{
    ui->setupUi(this);
	Init();
    connect(ui->pushButton_Check,SIGNAL(clicked()),this,SLOT(onPushbutton_Check()));
}

Comm_check::~Comm_check()
{
    delete ui;
}
void Comm_check::Init()
{
	ui->label->setText(tr("Verify the legitimacy of communication include the uniqueness test of MAC and IP ,The setting of VLAN"));
	ui->pushButton_Check->setText(tr("Check"));
	ui->textEdit->clear();
}

void Comm_check::AddOneErrToArea(QString str)
{
	ui->textEdit->append(str);
}

void Comm_check::Checkfile()
{
	Point->Comunication_Check(ErrList);
}
void Comm_check::onPushbutton_Check()
{


	ui->textEdit->clear();
	Checkfile();
    if(ErrList.size()==0)
    {
        ui->textEdit->append(tr("Checking finish"));
    }
	for (int i = 0; i < ErrList.size(); i++)
	{
		AddOneErrToArea(ErrList[i]);
	}
    if(ErrList.size()==0)
    {
        ui->textEdit->append(tr("There is no error"));
    }
}
void Comm_check::SetPoint(ScdTree *sPoint)
{
	
	Point = sPoint;
}

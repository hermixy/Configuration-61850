﻿#include "stationpara.h"
#include "ui_stationpara.h"

StationPara::StationPara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StationPara)
{
    ui->setupUi(this);
    ui->pushButton_ok->setText(tr("Ok"));
    ui->pushButton_cancel->setText(tr("Cancel"));
    ui->label_ver->setText(tr("Version"));
    ui->label_Line->setText(tr("Line"));
    ui->label_Project->setText(tr("ProjectName"));
    ui->label_vendor->setText(tr("Verdor"));
    connect(ui->pushButton_ok,SIGNAL(clicked(bool)),this,SLOT(pushbutton_ok()));
    connect(ui->pushButton_cancel,SIGNAL(clicked(bool)),this,SLOT(pushbutton_cancel()));
}

StationPara::~StationPara()
{
    delete ui;
}
void StationPara::pushbutton_ok()
{   vendor = ui->lineEdit_vendor->text();
    Line = ui->lineEdit_Line->text();
    ProjectName = ui->lineEdit_project->text();
    Version = ui->lineEdit_ver->text();
    accept();
}
void StationPara::pushbutton_cancel()
{
    reject();
}
void StationPara::display(int state)
{
	if (state == 2)
	{
		ui->label_Line->hide();
		ui->lineEdit_Line->hide();
	}
    ui->lineEdit_Line->setText(Line);
	ui->lineEdit_project->setText(ProjectName);
    ui->lineEdit_vendor->setText(vendor);
    ui->lineEdit_ver->setText(Version);
}

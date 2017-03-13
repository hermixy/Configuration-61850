﻿#include "importoneied.h"
#include "ui_importoneied.h"

ImportOneIed::ImportOneIed(QWidget *parent,ScdTree *point) :
    QDialog(parent),
    ui(new Ui::ImportOneIed)
{
    ui->setupUi(this);
    
    SCDPoint = point;
    this->setWindowTitle(tr("Import IED"));
    connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(Action_loadfile()));
    connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(Action_button_ok()));
    connect(ui->pushButton_cancel,SIGNAL(clicked()),this,SLOT(Action_button_cancle()));
}

ImportOneIed::~ImportOneIed()
{
    delete ui;
}
void ImportOneIed::InitDlg()
{
	if (state==1)
	{
		ui->label_doc->setText(tr("Select a CID File,make sure the IED name is unique"));
	}
	else if (state==2)
	{
		ui->label_doc->setText(tr("Select a ICD File,make sure the IED name is unique"));

	}

    ui->label_name->setText(tr("IED Name:"));
    ui->label_file->setText(tr("IED File:"));
    ui->pushButton_open->setText(tr("Browse"));
    ui->pushButton_ok->setText(tr("Ok"));
    ui->pushButton_cancel->setText(tr("Cancel"));

}
void ImportOneIed::Action_loadfile()
{
	QString fileName;
	if (state==1)
	{
		 fileName = QFileDialog::getOpenFileName(this,
			tr("Select CID "),
			QDir::currentPath(),
			tr("CID Files (*.CID)"));
	}
	else if (state==2)
	{
		 fileName = QFileDialog::getOpenFileName(this,
			tr("Select ICD "),
			QDir::currentPath(),
			tr("ICD Files (*.ICD)"));
	}

            if (!fileName.isNull())
            {
                ui->lineEdit_file->setText(fileName);

              if (LoadIEDFile(fileName)==DO_FAIL)
              {
                 //QMessageBox::about(0,tr("Alarm"),tr("Import IED File False!"));
				  ui->lineEdit_file->clear();
				  ui->lineEdit_name->clear();
                  return;
              }
			  else
			  {
                  QString strIEDname = SCDPoint->GetIEDName();
                  strfilename =fileName;
				  ui->lineEdit_name->setText(strIEDname);
				  return;
			  }
            }
            
}

void ImportOneIed::Action_button_ok()
{
    int len = ui->lineEdit_name->text().length();
     QString str1 =ui->lineEdit_name->text();
    for(int i =0;i<len;i++)
    {

        if(( str1.at(i)=='/')||(str1.at(i)=='\\')||(str1.at(i)==' '))
        {
            QMessageBox::about(0,tr("Alarm"),tr("The IED name can not contain '/','\\',and space!"));
               return;
        }
    }
    if(SCDPoint->CheckIEDName(ui->lineEdit_name->text())==DO_FAIL)
    {
     QMessageBox::about(0,tr("Alarm"),tr("The IED Name is exist!"));
        return;
    }
    accept();
}

void ImportOneIed::Action_button_cancle()
{
    reject();
}
int ImportOneIed::LoadIEDFile(QString fileName)
{
      int irecode;
      //irecode = SCDPoint->CheckIEDFile(fileName);
      irecode=SCDPoint->LoadIEDFile(fileName);
      //irecode = SCDPoint->CheckIEDName(fileName);
      return irecode;
}
QString ImportOneIed::GetIEDName()
{
	QString str = ui->lineEdit_name->text();
	return str;
}
QString ImportOneIed::GetFileName()
{
     return strfilename;
}
void ImportOneIed::setState(int sta)
{
	state = sta;
}

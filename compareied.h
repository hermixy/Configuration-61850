﻿#ifndef COMPAREIED_H
#define COMPAREIED_H

#include <QDialog>
#include "ui_compareied.h"
#include<QStandardItemModel>
#include<QMap>
class CompareIED : public QDialog
{
	Q_OBJECT

public:
	CompareIED(QWidget *parent = 0);
	~CompareIED();
        QStandardItemModel *ModelDataSet;
      QStandardItemModel *ModelInput;
      QStandardItemModel *ModelControlBLK;
	  QStringList headerlist;
      void Init();
      int state;
      void ChangeIndex(int);
      void ChangeDispaly(int);
      void DisplayDataSet(QMap<QString,QString>&,QMap<QString,QString>&);
      void DisplayInput(QMap<QString,QString>&,QMap<QString,QString>&);
      void DisplayCBLK(QMap<QString,QString>&,QMap<QString,QString>&);
  private slots:
      void On_Pushbutton_Replace_1();
      void On_Pushbutton_Replace_2();
      void On_Pushbutton_Ignore();
      void On_Pushbutton_Cancel();
private:
	Ui::CompareIED ui;
};

#endif // COMPAREIED_H

﻿#ifndef RELOAD_H
#define RELOAD_H

#include <QDialog>
#include<QStandardItem>
#include<QItemSelectionModel>
namespace Ui {
class ReLoad;
}

class ReLoad : public QDialog
{
    Q_OBJECT

public:
    explicit ReLoad(QWidget *parent = 0);
    ~ReLoad();
    void Init_dlg();
    void Display();
    QStringList IEDList;
    QStandardItemModel *Model;
    QItemSelectionModel *ModelSlection;
    QString IED_select;
private slots:
    void Pushbutton_apply();
    void Pushbutton_cancel();
private:
    Ui::ReLoad *ui;
};

#endif // RELOAD_H

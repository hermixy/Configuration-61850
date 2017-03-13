﻿#ifndef DROPTABLE_H
#define DROPTABLE_H

#include <QTableWidget>
#include<QMouseEvent>
#include<QEvent>
class DropTable : public QTableView
{
	Q_OBJECT

public:
	DropTable(QWidget *parent = 0);
protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

signals:
	void senddragMoveEvent(QDropEvent *event);
};

#endif

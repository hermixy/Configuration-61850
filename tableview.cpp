﻿#include "tableview.h"

TableView::TableView(QWidget *parent) :
    QTableView(parent)
{
         setAcceptDrops(true);
        setDragDropMode(QAbstractItemView::DragDrop);
        //setDragEnabled(true);
        //setDropIndicatorShown(true);


}
TableView::~TableView()
{
}
  void TableView::dragEnterEvent(QDragEnterEvent *event)
{
         event->setDropAction(Qt::MoveAction);
        event->accept();
        SenddragEnterEvent(event);
        event->acceptProposedAction();
        QTableView::dragEnterEvent(event);

}
 void TableView::dropEvent(QDropEvent *event)
{
            event->setDropAction(Qt::MoveAction);
            event->accept();
            SenddropEvent(event);
            event->acceptProposedAction();
            QTableView::dropEvent(event);

}

 void TableView::dragMoveEvent(QDragMoveEvent *event)
{
        event->setDropAction(Qt::MoveAction);
        event->accept();
        event->acceptProposedAction();
        SenddragMoveEvent(event);
        QTableView::dragMoveEvent(event);

}

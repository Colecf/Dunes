#include "passdata.h"

PassData::PassData(QObject *parent) : QMimeData()
{
    //QMimeData::QMimeData();
}

void PassData::setQListWidgetItem(QListWidget *list)
{
    widget_item = list->currentItem();
}
QListWidgetItem* PassData::getQListWidgetItem()
{
    return widget_item;
}

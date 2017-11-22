#include "passdata.h"

PassData::PassData() : QMimeData()
{
}

void PassData::setQListWidgetItem(QListWidget *list)
{
    widget_item = list->currentItem();
}
QListWidgetItem* PassData::getQListWidgetItem()
{
    return widget_item;
}

void PassData::setIndex(int index)
{
    idx = index;
}
int PassData::getIndex()
{
    return idx;
}

void PassData::setHeight(int new_height)
{
    height = new_height;
}

int PassData::getHeight()
{
    return height;
}

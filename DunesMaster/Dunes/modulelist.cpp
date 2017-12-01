#include "modulelist.h"
#include "modulelistitem.h"

ModuleList::ModuleList(QWidget *parent) : QListWidget(parent)
{
}

void ModuleList::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
           dragStartPosition = event->pos();
    QListWidget::mousePressEvent(event);
}

void ModuleList::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
    {
        return;
    }
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
    {
        return;
    }

    QDrag *drag = new QDrag(this);

    QMimeData *mimeData = new QMimeData;
    mimeData->setProperty("index", -1);
    mimeData->setProperty("blocktype", ((ModuleListItem*)currentItem())->getType());
    drag->setMimeData(mimeData);

    drag->exec(Qt::CopyAction);
}

#include "modulelist.h"

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
        PassData *mimeData = new PassData;

        mimeData->setText(currentItem()->text());
        mimeData->setQListWidgetItem(this);
        mimeData->setIndex(-1);
        drag->setMimeData(mimeData);
        //drag->setPixmap(iconPixmap);

        Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
        //addItem("hello new block");
}

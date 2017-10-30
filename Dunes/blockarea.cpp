#include "blockarea.h"
//Remove QDebug later
#include <QDebug>
BlockArea::BlockArea(QWidget *parent) : QScrollArea(parent)
{
    QWidget* widget = new QWidget;
    m_layout = new QVBoxLayout;
    m_layout->setAlignment(Qt::AlignTop);
    widget->setLayout(m_layout);
    setWidget(widget);
    setWidgetResizable(true);

    setAcceptDrops(true);
}

bool BlockArea::createBlock(ModuleType blockType)
{
    BaseModule* module = BaseRegistry::createInstance(blockType);
    m_layout->addWidget(module);
    return true;
}

QVBoxLayout* BlockArea::getLayout()
{
    return m_layout;
}

void BlockArea::dragEnterEvent(QDragEnterEvent *event)
{
    //if (event->mimeData()->hasFormat("text/plain"))
            event->acceptProposedAction();
}

void BlockArea::dropEvent(QDropEvent *event)
{
    //textBrowser->setPlainText(event->mimeData()->text());
    //mimeTypeCombo->clear();
   //mimeTypeCombo->addItems(event->mimeData()->formats());
   const QMimeData* itemData = event->mimeData();

    //qInfo() << event->mimeData()->text();
    //qInfo() << ((PassData*)test)->getQListWidgetItem()->text();

    QListWidgetItem *block = ((PassData*)itemData)->getQListWidgetItem();
    createBlock((((ModuleListItem*)block)->getType()));
    event->acceptProposedAction();
}

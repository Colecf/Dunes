#include "blockarea.h"
//Remove QDebug later
#include <QDebug>
BlockArea::BlockArea(QWidget *parent) : QScrollArea(parent)
{
    QWidget* widget = new QWidget;
    m_layout = new QGridLayout;
    m_layout->setAlignment(Qt::AlignTop);
    widget->setLayout(m_layout);
    setWidget(widget);
    setWidgetResizable(true);

    setAcceptDrops(true);

    moduleCount = 0;
}

bool isIndented(BaseModule* module)
{
    if(dynamic_cast<ScopeModule*>(module) != nullptr) {
        return true;
    }
    return false;
}

bool BlockArea::createBlock(ModuleType blockType)
{
    // whight: for now, this always creates blocks in the current nest
    BaseModule* module = BaseRegistry::createInstance(blockType);
    int desiredRowSpan = 1, desiredColSpan = 2;
    int row = 0, col = 0, rowSpan, colSpan;
    QWidget* prevWidget = nullptr;

    if(moduleCount != 0)
    {
        prevWidget = m_layout->itemAt(moduleCount-1)->widget();
        m_layout->getItemPosition(moduleCount-1, &row, &col, &rowSpan, &colSpan);
    }
    if(isIndented(module))
    {
        /* whight: other way of doing indentation, not grid, could also add
         * horizontal layout with spacer to vertical layout?
        QWidget* indentedBlock = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout;
        layout->setAlignment(Qt::AlignLeft);
        indentedBlock->setLayout(layout);
        layout->addSpacerItem(new QSpacerItem(50, 0));
        layout->addWidget(module);
        m_layout->addWidget(indentedBlock);
        */
        m_layout->addWidget(module, moduleCount++, col+1, desiredRowSpan, desiredColSpan);
    }
    else
    {
        if(isIndented((BaseModule*)prevWidget))
        {
            m_layout->addWidget(module, moduleCount++, col+1, desiredRowSpan, desiredColSpan);
        }
        else
        {
            m_layout->addWidget(module, moduleCount++, col, desiredRowSpan, desiredColSpan);
        }
    }
    return true;
}

QGridLayout* BlockArea::getLayout()
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

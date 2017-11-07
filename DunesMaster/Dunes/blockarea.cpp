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
}

bool BlockArea::createBlock(ModuleType blockType)
{
    // whight: for now, this always creates blocks in the current nest
    BaseModule* module = BaseRegistry::createInstance(blockType);
    connect(module, SIGNAL(keyPressed(BaseModule*, QKeyEvent*)), this, SLOT(keyPressedInModule(BaseModule*, QKeyEvent*)));

    // whight: other way of doing indentation, not grid, could also add
    // horizontal layout with spacer to vertical layout?
    //QWidget* indentedBlock = new QWidget();
    //QHBoxLayout* layout = new QHBoxLayout;
    //layout->setAlignment(Qt::AlignLeft);
    //indentedBlock->setLayout(layout);
    //layout->addSpacerItem(new QSpacerItem(50, 0));
    //layout->addWidget(module);
    //m_layout->addWidget(indentedBlock);


    m_layout->addWidget(module, m_layout->count(), 0, 1, 1);
    return true;
}

void BlockArea::keyPressedInModule(BaseModule* mod, QKeyEvent* event)
{
    if(event->key() == Qt::Key_Tab || event->key() == Qt::Key_Backtab) {
        int index = m_layout->indexOf(mod);
        int row, col, row2, col2, rowSpan, colSpan;
        m_layout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);

        int newCol = col;

        if(event->key() == Qt::Key_Backtab && col > 0) {
            newCol--;
        } else if(index > 0) {
            int row2, col2;

            //Find the item on the previous row, to know if we can indent past it
            for(int i=0; i<m_layout->count(); i++) {
                m_layout->getItemPosition(i, &row2, &col2, &rowSpan, &colSpan);
                if(row2 == row-1) {
                    break;
                }
            }

            if(col <= col2)
                newCol++;
        }

        if(newCol != col) {
            m_layout->addWidget(mod, row, newCol, 1, 1);
        }

        // Unindent everything after this if this was an unindent
        // stop unindenting if you get to something at a lesser column
        if(newCol < col) {
            bool done = false;
            for(row++; row < m_layout->count() && !done; row++) {
                for(int i=0; i<m_layout->count(); i++) {
                    m_layout->getItemPosition(i, &row2, &col2, &rowSpan, &colSpan);
                    if(row2 == row) {
                        if(col2 >= col) {
                            m_layout->addWidget(m_layout->itemAt(i)->widget(), row2, col2-1);
                        } else {
                            done = true;
                        }
                        break;
                    }
                }
            }
        }
    }
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

void BlockArea::generateCode(){
    QString code = "";
    for(int idx = 0; idx < m_layout->count(); idx++){
        QWidget* const item = m_layout->itemAt(idx)->widget();
        if(BaseModule* module = dynamic_cast<BaseModule*>(item)){
            code += module->getCode();
        }
    }
    qInfo() << code;
}

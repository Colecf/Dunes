#include "blockarea.h"
#include <stack>
#include <limits>
//Remove QDebug later
#include <QDebug>
#define FROM_MOD_LIST -1
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

bool BlockArea::createBlockAt(ModuleType blockType, int module_location)
{
    // whight: for now, this always creates blocks in the current nest
    BaseModule* module = BaseRegistry::createInstance(blockType);
    connect(module, SIGNAL(keyPressed(BaseModule*, QKeyEvent*)), this, SLOT(keyPressedInModule(BaseModule*, QKeyEvent*)));
    int desiredRowSpan = 1, desiredColSpan = 1;
    int col = 0;


    if(m_layout->count() != 0)
    {
        moveBlocksDown(module_location);
    }
    m_layout->addWidget(module, module_location, col, desiredRowSpan, desiredColSpan);
    return true;
}

//need to move blocks up
void BlockArea::moveBlocksDown(int module_location)
{
    int desiredRowSpan = 1, desiredColSpan = 1;
    QWidget* prevWidget = nullptr;
    int mod_count = m_layout->count() - 1;

    std::unordered_map<int, int> *rowToCol = createRowToCol();

    for(; module_location <= mod_count; module_location++)
    {
        prevWidget = m_layout->itemAtPosition(module_location, getCol(rowToCol, module_location))->widget();
        m_layout->addWidget(prevWidget, module_location + 1, getCol(rowToCol, module_location), desiredRowSpan, desiredColSpan);
    }
}

void BlockArea::moveBlocksDownUntil(int start, int end)
{
    int desiredRowSpan = 1, desiredColSpan = 1;
    QWidget* prevWidget = nullptr;

    std::unordered_map<int, int> *rowToCol = createRowToCol();
    for(; start < end; start++)
    {
        prevWidget = m_layout->itemAtPosition(start, getCol(rowToCol, start))->widget();
        m_layout->addWidget(prevWidget, start + 1, getCol(rowToCol, start), desiredRowSpan, desiredColSpan);
    }
}

void BlockArea::moveBlocksUp(int start, int end)
{
    int desiredRowSpan = 1, desiredColSpan = 1;
    QWidget* prevWidget = nullptr;

    std::unordered_map<int, int> *rowToCol = createRowToCol();
    for(; start <= end; start++)
    {
        prevWidget = m_layout->itemAtPosition(start, getCol(rowToCol, start))->widget();
        m_layout->addWidget(prevWidget, start - 1, getCol(rowToCol, start), desiredRowSpan, desiredColSpan);
    }
}
QGridLayout* BlockArea::getLayout()
{
    return m_layout;
}

void BlockArea::dragEnterEvent(QDragEnterEvent *event)
{
      event->acceptProposedAction();
      QScrollArea::dragEnterEvent(event);
}

void BlockArea::dropEvent(QDropEvent *event)
{

    const QMimeData* itemData = event->mimeData();
    int y_coord = m_layout->parentWidget()->mapFrom(this, event->pos()).y();
    if(((PassData*)itemData)->getIndex() == FROM_MOD_LIST)
    {
        QListWidgetItem *block = ((PassData*)itemData)->getQListWidgetItem();
        if(m_layout->count() == 0)
        {
            createBlock((((ModuleListItem*)block)->getType()));
            event->acceptProposedAction();
            return;
        }
        //qInfo() << m_layout->parentWidget()->mapFrom(this, event->pos()) << m_layout->parentWidget()->geometry();
        int module_location = y_coord / (m_layout->itemAt(0)->widget()->height() + m_layout->verticalSpacing());
        //qInfo() << module_location << event->pos().y() <<(m_layout->itemAt(0)->widget()->height() + m_layout->verticalSpacing());

        if(module_location > m_layout->count())
        {
            createBlock((((ModuleListItem*)block)->getType()));
        }
        else
        {
            createBlockAt((((ModuleListItem*)block)->getType()), module_location);
        }
        event->acceptProposedAction();
    }
    else
    {
        int index = ((PassData*)itemData)->getIndex();
        int module_location = y_coord / (m_layout->itemAt(0)->widget()->height() + m_layout->verticalSpacing());
        if(module_location > index)
        {
            if(module_location >= m_layout->count())
                module_location = m_layout->count() - 1;
            std::unordered_map<int, int> *rowToCol = createRowToCol();
            QWidget *block = nullptr;
            block = m_layout->itemAtPosition(index, getCol(rowToCol, index))->widget();
            if(module_location > index)
                moveBlocksUp((index < module_location) ? index : module_location, (index > module_location) ? index : module_location);
            m_layout->addWidget(block, module_location, 0, 1, 1);
            connect(block, SIGNAL(keyPressed(BaseModule*, QKeyEvent*)), this, SLOT(keyPressedInModule(BaseModule*, QKeyEvent*)));
        }
        else if(index > module_location)
        {
            std::unordered_map<int, int> *rowToCol = createRowToCol();
            QWidget *block = nullptr;
            block = m_layout->itemAtPosition(index, getCol(rowToCol, index))->widget();
            moveBlocksDownUntil((index < module_location) ? index : module_location, (index > module_location) ? index : module_location);
            m_layout->addWidget(block, module_location, 0, 1, 1);
            connect(block, SIGNAL(keyPressed(BaseModule*, QKeyEvent*)), this, SLOT(keyPressedInModule(BaseModule*, QKeyEvent*)));
        }
       event->acceptProposedAction();
    }
    QScrollArea::dropEvent(event);

}

std::unordered_map<int, int>* BlockArea::createRowToCol(){
    std::unordered_map<int, int> *rowToCol = new std::unordered_map<int, int>();
    for(int idx = 0; idx < m_layout->count(); idx++){
        int row, col, rowSpan, colSpan;
        m_layout->getItemPosition(idx, &row, &col, &rowSpan, &colSpan);
        rowToCol->insert({row, col});
    }
    return rowToCol;
}

int BlockArea::getCol(const std::unordered_map<int, int> *dict, int row){
    auto found = dict->find(row);
    if(found == dict->end()){
        qErrnoWarning("Error: Could not find Block given key %d", row);
        return -1;
    }
    return found->second;

}

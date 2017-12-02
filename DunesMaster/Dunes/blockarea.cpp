#include "blockarea.h"
#include <stack>
#include <limits>
//Remove QDebug later
#include <QDebug>

#define FROM_MOD_LIST -1
#define COL_WIDTH 250

BlockArea::BlockArea(QWidget *parent) : QScrollArea(parent)
{
    QWidget* widget = new QWidget;
    m_layout = new QGridLayout;
    m_layout->setAlignment(Qt::AlignTop);

    //TODO you shouldn't need this, but on mac vertical spacing is -1 for some reason
#ifdef __APPLE__
    m_layout->setVerticalSpacing(6);
#endif
    widget->setLayout(m_layout);
    setWidget(widget);
    setWidgetResizable(true);

    setAcceptDrops(true);
}

bool BlockArea::createBlock(ModuleType blockType)
{
    // whight: for now, this always creates blocks in the current nest
    BaseModule* module = BaseRegistry::createInstance(blockType);
    module->setFixedWidth(COL_WIDTH);
    connect(module, SIGNAL(keyPressed(BaseModule*, QKeyEvent*)), this, SLOT(keyPressedInModule(BaseModule*, QKeyEvent*)));
    m_layout->addWidget(module, m_layout->count(), 0, 1, 1);
    return true;
}

// to create a block at a specific column and return the widget to set options on it later
BaseModule* BlockArea::createBlock(ModuleType blockType, int col)
{
    BaseModule* module = BaseRegistry::createInstance(blockType);
    module->setFixedWidth(COL_WIDTH);
    connect(module, SIGNAL(keyPressed(BaseModule*, QKeyEvent*)), this, SLOT(keyPressedInModule(BaseModule*, QKeyEvent*)));
    m_layout->addWidget(module, m_layout->count(), col, 1, 1);
    return module;
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
    } else if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
        int row, col, rowSpan, colSpan;
        if(m_layout->indexOf(mod) < 0) {
            // We should never get here
            qInfo() << "ERROR: Negative index when trying to remove module!!\n";
            return;
        }
        m_layout->getItemPosition(m_layout->indexOf(mod), &row, &col, &rowSpan, &colSpan);
        m_layout->removeWidget(mod);
        mod->setParent(NULL);

        moveBlocksUp(row+1, -1);
    }
}

bool BlockArea::createBlockAt(ModuleType blockType, int module_location)
{
    // whight: for now, this always creates blocks in the current nest
    BaseModule* module = BaseRegistry::createInstance(blockType);
    module->setFixedWidth(COL_WIDTH);
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

//Moves all blocks down 1 space starting from module location
void BlockArea::moveBlocksDown(int module_location)
{
    int desiredRowSpan = 1, desiredColSpan = 1;
    QWidget* prevWidget = nullptr;
    int mod_count = m_layout->count() - 1;

    auto rowToCol = createRowToCol();

    for(; module_location <= mod_count; module_location++)
    {
        prevWidget = m_layout->itemAtPosition(module_location, getCol(rowToCol, module_location))->widget();
        m_layout->addWidget(prevWidget, module_location + 1, getCol(rowToCol, module_location), desiredRowSpan, desiredColSpan);
    }
}
//Moves all blocks down 1 space starting at start and stops before end
void BlockArea::moveBlocksDownUntil(int start, int end)
{
    int desiredRowSpan = 1, desiredColSpan = 1;
    QWidget* prevWidget = nullptr;

    auto rowToCol = createRowToCol();
    for(; start < end; start++)
    {
        prevWidget = m_layout->itemAtPosition(start, getCol(rowToCol, start))->widget();
        m_layout->addWidget(prevWidget, start + 1, getCol(rowToCol, start), desiredRowSpan, desiredColSpan);
    }
}
/* Moves blocks upwards in the layout by 1 space starting at start
 * and ending at end. */
void BlockArea::moveBlocksUp(int start, int end)
{
    int lastRow = m_layout->count();
    if(end > lastRow || end < 0)
        end = lastRow;
    else
        end--;
    if(start < 0)
        return;
    int desiredRowSpan = 1, desiredColSpan = 1;
    QWidget* prevWidget = nullptr;
    auto rowToCol = createRowToCol();
    for(; start <= end; start++)
    {
        int col = getCol(rowToCol, start);
        if(col < 0)
            return;
        prevWidget = m_layout->itemAtPosition(start, col)->widget();
        m_layout->addWidget(prevWidget, start - 1, getCol(rowToCol, start), desiredRowSpan, desiredColSpan);
    }
}
QGridLayout* BlockArea::getLayout()
{
    return m_layout;
}
//Necessary for dragMoveEvent and drop event
void BlockArea::dragEnterEvent(QDragEnterEvent *event)
{
      event->acceptProposedAction();
      QScrollArea::dragEnterEvent(event);
}

//Given the y coordinate of the mouse, figures out which row you should insert the block to
int BlockArea::mouseCoordToModuleLocation(int yCoord) {
    int moduleLocation = 0;
    auto rowToCol = createRowToCol();
    while(yCoord > 0 && moduleLocation < m_layout->count()) {
        yCoord -= m_layout->itemAtPosition(moduleLocation, getCol(rowToCol, moduleLocation))->widget()->height() + m_layout->verticalSpacing();
        moduleLocation++;
    }
    return moduleLocation;
}

//Adds in indicator for where the drag and drop block will go.
void BlockArea::dragMoveEvent(QDragMoveEvent *event)
{
    qInfo() << m_layout->verticalSpacing();
    if(m_layout->count() > 0 && line != nullptr)
    {
        int y_coord = m_layout->parentWidget()->mapFrom(this, event->pos()).y();
        int module_location = mouseCoordToModuleLocation(y_coord);
        int end_module_pix = 0;
        auto rowToCol = createRowToCol();
        for(int i=0; i<module_location; i++) {
            end_module_pix += m_layout->itemAtPosition(i, getCol(rowToCol, i))->widget()->height() + m_layout->verticalSpacing();
        }
        if(module_location != cur_line_location)
        {
            if(module_location > m_layout->count())
            {
                end_module_pix = m_layout->count() * (m_layout->itemAt(0)->widget()->height() + m_layout->verticalSpacing());
            }
            delete line;
            line = new QFrame(m_layout->parentWidget());
            line->setObjectName("Line");
            line->setGeometry(0, end_module_pix + m_layout->verticalSpacing() / 2, m_layout->parentWidget()->size().width(), m_layout->verticalSpacing());
            line->setLineWidth(m_layout->verticalSpacing() / 2);
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Plain);
            line->setStyleSheet("#Line { color: green;}");
            line->show();
            cur_line_location = module_location;
        }
    }
    else
    {
        line = new QFrame(m_layout->parentWidget());
    }
}
//Takes the dropped block and inserts into the right spot based on mouse position. Also removes indicator afterwards.
void BlockArea::dropEvent(QDropEvent *event)
{
    const QMimeData* itemData = event->mimeData();
    int y_coord = m_layout->parentWidget()->mapFrom(this, event->pos()).y();
    int drop_location = mouseCoordToModuleLocation(y_coord);
    int index = itemData->property("index").toInt();
    if(index == FROM_MOD_LIST)
    {
        ModuleType blockType = static_cast<ModuleType>(itemData->property("blocktype").toInt());
        if(m_layout->count() == 0)
        {
            createBlock(blockType);
            event->acceptProposedAction();
            return;
        }

        if(drop_location > m_layout->count())
        {
            createBlock(blockType);
        }
        else
        {
            createBlockAt(blockType, drop_location);
        }
        event->acceptProposedAction();
    }
    else
    {
        auto rowToCol = createRowToCol();
        if(drop_location > index)
        {
            if(drop_location >= m_layout->count())
                drop_location = m_layout->count();
            QWidget *draggedBlock = m_layout->itemAtPosition(index, getCol(rowToCol, index))->widget();
            m_layout->removeWidget(draggedBlock);
            moveBlocksUp(index + 1, drop_location);
            m_layout->addWidget(draggedBlock, drop_location - 1, 0, 1, 1);
        }
        else if(index > drop_location)
        {
            QWidget *block = m_layout->itemAtPosition(index, getCol(rowToCol, index))->widget();
            moveBlocksDownUntil(drop_location, index);
            m_layout->addWidget(block, drop_location, 0, 1, 1);
        }
        event->acceptProposedAction();
    }
    QScrollArea::dropEvent(event);
    line->setGeometry(0,0,0,0);
}

std::shared_ptr<std::unordered_map<int, int>> BlockArea::createRowToCol(){
    std::shared_ptr<std::unordered_map<int, int>> rowToCol = std::make_shared<std::unordered_map<int, int>>();
    for(int idx = 0; idx < m_layout->count(); idx++){
        int row, col, rowSpan, colSpan;
        m_layout->getItemPosition(idx, &row, &col, &rowSpan, &colSpan);
        rowToCol->insert({row, col});
    }
    return rowToCol;
}

int BlockArea::getCol(std::shared_ptr<std::unordered_map<int, int>> dict, int row){
    auto found = dict->find(row);
    if(found == dict->end()){
        qErrnoWarning("Error: Could not find Block given key %d", row);
        return -1;
    }
    return found->second;
}

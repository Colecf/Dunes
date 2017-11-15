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
    int desiredRowSpan = 1, desiredColSpan = 2;
    int row = 0, col = 0;


    if(m_layout->count() != 0)
    {
        moveBlocksDown(module_location);
    }
    m_layout->addWidget(module, module_location, col, desiredRowSpan, desiredColSpan);
    return true;
}


void BlockArea::moveBlocksDown(int module_location)
{
    int desiredRowSpan = 1, desiredColSpan = 2;
    int row = 0, col = 0, rowSpan, colSpan;
    QWidget* prevWidget = nullptr;
    int mod_count = m_layout->count() - 1;

    std::unordered_map<int, int> *rowToCol = new std::unordered_map<int, int>();
    for(int idx = 0; idx < m_layout->count(); idx++){
        int row, col, rowSpan, colSpan;
        m_layout->getItemPosition(idx, &row, &col, &rowSpan, &colSpan);
        rowToCol->insert({row, col});
    }

    for(; module_location <= mod_count; module_location++)
    {

        getCol(rowToCol, module_location);
        prevWidget = m_layout->itemAtPosition(module_location, getCol(rowToCol, module_location))->widget();
        m_layout->addWidget(prevWidget, module_location + 1, getCol(rowToCol, module_location), desiredRowSpan, desiredColSpan);
    }
}

QGridLayout* BlockArea::getLayout()
{
    return m_layout;
}

void BlockArea::dragMoveEvent(QDragMoveEvent *event)
{
  //  qInfo() << event->pos();
}
void BlockArea::dragEnterEvent(QDragEnterEvent *event)
{
     //if (event->mimeData()->hasFormat("text/plain"))
           event->acceptProposedAction();
           QScrollArea::dragEnterEvent(event);
}

void BlockArea::dropEvent(QDropEvent *event)
{
    //textBrowser->setPlainText(event->mimeData()->text());
    //mimeTypeCombo->clear();
   //mimeTypeCombo->addItems(event->mimeData()->formats());

  const QMimeData* itemData = event->mimeData();

    //qInfo() << "DROPPED: " << event->pos() << event->pos().y() << event->pos().x();

//found that blocks were ~37 units tall

    int module_location = event->pos().y() / 37;
    //qInfo() << "/37 RESULT: " << module_location;



    if(((PassData*)itemData)->getIndex() == FROM_MOD_LIST)
    {
        QListWidgetItem *block = ((PassData*)itemData)->getQListWidgetItem();
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
        int row = 0, col = 0, rowSpan, colSpan;
        int index = ((PassData*)itemData)->getIndex();
        //need type from base module or something

        std::unordered_map<int, int> *rowToCol = createRowToCol();

        qInfo() << "not from modlist index: " << ((PassData*)itemData)->getIndex() << m_layout->count();

        QWidget *block = m_layout->itemAtPosition(index, getCol(rowToCol, index))->widget();
        qInfo() << block;
        if(module_location > m_layout->count() && index < m_layout->count() - 1)
        {
            qInfo() <<"ADD TO END FROM BLOCKAREA";
            QWidget *block = m_layout->itemAtPosition(((PassData*)itemData)->getIndex(), getCol(rowToCol, index))->widget();
            //m_layout->getItemPosition(m_layout->count()-1, &row, &col, &rowSpan, &colSpan);
            moveBlocksDown(module_location);
            m_layout->addWidget(block, module_location, col, 1, 1);
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

void BlockArea::generateCode(){
    QString code = "";
    // Create mapping from row to column, do this instead of row to module because we can't get col from module
    std::unordered_map<int, int> *rowToCol = createRowToCol();
    // Stack of every parent-block's row (while, if, scope, foreach). Get the block via casting a widget w/ itemAtPosition
    std::stack<int> *parentRowStack = new std::stack<int>;
    for(int row = 0; row < m_layout->count(); row++){
        int col, prevModuleCol;
        if((col = getCol(rowToCol, row)) == -1){
            qErrnoWarning("Error: col must integer >= 0");
            return;
        }
        QWidget* const item = m_layout->itemAtPosition(row, col)->widget();
        if(BaseModule *module = dynamic_cast<BaseModule*>(item)){
            int parentCol;
            // If we have parent blocks, get the parentCol and compare with current col
            if(!parentRowStack->empty() && (parentCol = getCol(rowToCol, parentRowStack->top())) != -1){
                // If equal, we know we need to pop off all block rows that have a corresponding col >= than the current block's col
                while(parentCol >= col){
                    parentRowStack->pop();
                    if(!parentRowStack->empty()){
                        parentCol = getCol(rowToCol, parentRowStack->top());
                    }
                    else{
                        // In the case that parentCol = col = 0, we don't want it to pop again.
                        // Set it to large random negative # to not trigger bottom if-statement
                        parentCol = std::numeric_limits<int>::min();
                    }
                }
                // If the parent is a parent to this module, add it to the parent's children
                if(parentCol+1 == col){
                    QWidget* const parent = m_layout->itemAtPosition(parentRowStack->top(), parentCol)->widget();
                    if(BaseModule *parentModule = dynamic_cast<BaseModule*>(parent)){
                        parentModule->children->push_back(module);
                    }
                }
            }
            // If it's a scope, push on the row of the block
            if(dynamic_cast<ScopeModule*>(module)){
                parentRowStack->push(row);
                module->children = new std::vector<BaseModule*>;
            }
        }
        prevModuleCol = col;
    }
    for(int row = 0; row < m_layout->count(); row++){
        int col;
        if((col = getCol(rowToCol, row)) == -1){
            qErrnoWarning("Error: col must integer >= 0");
            return;
        }
        if(col == 0){
            QWidget* const item = m_layout->itemAtPosition(row, col)->widget();
            if(BaseModule *module = dynamic_cast<BaseModule*>(item)){
                code += module->getCode();
            }
        }
    }
    qInfo() << code;
}

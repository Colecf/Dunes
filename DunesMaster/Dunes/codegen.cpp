#include <unordered_map>
#include <stack>
#include <QDebug>
#include <QSaveFile>
#include <QTextStream>
#include <QDir>
#include "codegen.h"
#include "blockarea.h"

CodeGen::CodeGen()
{
}

CodeGen::CodeGen(BlockArea *blockarea)
{
    m_blockarea = blockarea;
}

QString CodeGen::generateCode(){
    QString code = "";
    // Create mapping from row to column, do this instead of row to module because we can't get col from module
    std::unordered_map<int, int> *rowToCol = m_blockarea->createRowToCol();
    // Stack of every parent-block's row (while, if, scope, foreach). Get the block via casting a widget w/ itemAtPosition
    QGridLayout *m_layout = m_blockarea->getLayout();
    std::stack<int> *parentRowStack = new std::stack<int>;
    for(int row = 0; row < m_layout->count(); row++){
        int col, prevModuleCol;
        if((col = m_blockarea->getCol(rowToCol, row)) == -1){
            qErrnoWarning("Error: col must integer >= 0");
            return NULL;
        }
        QWidget* const item = m_layout->itemAtPosition(row, col)->widget();
        if(BaseModule *module = dynamic_cast<BaseModule*>(item)){
            int parentCol;
            // If we have parent blocks, get the parentCol and compare with current col
            if(!parentRowStack->empty() && (parentCol = m_blockarea->getCol(rowToCol, parentRowStack->top())) != -1){
                // If equal, we know we need to pop off all block rows that have a corresponding col >= than the current block's col
                while(parentCol >= col){
                    parentRowStack->pop();
                    if(!parentRowStack->empty()){
                        parentCol = m_blockarea->getCol(rowToCol, parentRowStack->top());
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
        if((col = m_blockarea->getCol(rowToCol, row)) == -1){
            qErrnoWarning("Error: col must integer >= 0");
            return NULL;
        }
        if(col == 0){
            QWidget* const item = m_layout->itemAtPosition(row, col)->widget();
            if(BaseModule *module = dynamic_cast<BaseModule*>(item)){
                code += module->getCode();
            }
        }
    }
    return code;
}

void CodeGen::writeCode(QString filename){
    QString code = generateCode();
    QDir curDir = QDir::current();
    QString output = "output";
    QString absolutePath = curDir.absolutePath() + "/" + output;
    if(curDir.mkdir(output) || curDir.exists(output)){
        QSaveFile qSaveFile(absolutePath+ "/" +filename);
        if (qSaveFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&qSaveFile);
            stream << code;
            qSaveFile.commit();
            qInfo() << "saved to: " << absolutePath << endl;
        }
    }
}

#include "scopemodule.h"
#include "modulelistitem.h"

const QString ScopeModule::title = "Scope";
const QString ScopeModule::description = "Increases the scope of the input stream. Blocks in this scope must be indented. Initially does nothing, but when leaving it's indentation level it restores the input stream to what it was when it was when the scope block was reached.";

ScopeModule::ScopeModule()
{
    m_titleLabel->setText(title);
}

QString ScopeModule::getCode(){
    QString code = "scope();\n";
    if(this->children != NULL){
        for(size_t i = 0; i < this->children->size(); i++){
            code += this->children->at(i)->getCode();
        }
    }
    code += "pop();\n";
    return code;
}

QString ScopeModule::getConfig(QString col){
    return title + col + "\n";
}

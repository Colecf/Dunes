#include "scopemodule.h"
#include "modulelistitem.h"

const QString ScopeModule::title = "Scope";
const QString ScopeModule::description = "Scope Description";

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

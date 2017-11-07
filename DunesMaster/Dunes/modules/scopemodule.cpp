#include "scopemodule.h"
#include "modulelistitem.h"

const QString ScopeModule::title = "Scope";
const QString ScopeModule::description = "Scope Description";

ScopeModule::ScopeModule()
{
    m_titleLabel->setText(title);
}

QString ScopeModule::getCode(){
    return "scope();";
}

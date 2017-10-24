#include "scopemodule.h"
#include "modulelistitem.h"
ScopeModule::ScopeModule()
{

}

void ScopeModule::setUp(QListWidget* list)
{
    ModuleListItem *listItem = new ModuleListItem(QString("Scope"), QString("This is a scope description"), ModuleDL);
    list->addItem(listItem);

    BaseRegistry::registerType(ModuleScope, &createT<ScopeModule>);
}

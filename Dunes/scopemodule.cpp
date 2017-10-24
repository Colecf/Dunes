#include "scopemodule.h"
#include "modulelistitem.h"

const QString ScopeModule::title = "Scope";
const QString ScopeModule::description = "Scope Description";

ScopeModule::ScopeModule()
{
    setText("Scope");
}

void ScopeModule::setUp(QListWidget* list)
{
    ModuleListItem *listItem = new ModuleListItem(title, description, ModuleScope);
    list->addItem(listItem);

    BaseRegistry::registerType(ModuleScope, &createT<ScopeModule>);
}

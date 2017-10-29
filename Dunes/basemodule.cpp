#include "basemodule.h"
#include "modulelistitem.h"

BaseRegistry::map_type BaseRegistry::map;

const QString BaseModule::title = "Base";
const QString BaseModule::description = "Description";


void BaseModule::createModuleListItem(QListWidget* list, QString title, QString description, ModuleType type) {
    list->addItem(new ModuleListItem(title, description, type));
}

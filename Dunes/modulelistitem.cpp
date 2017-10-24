#include "modulelistitem.h"

ModuleListItem::ModuleListItem(QString title, QString desc, ModuleType t) : description(desc), type(t)
{
    setText(title);
    setToolTip(title);
}

QString ModuleListItem::getDescription()
{
    return description;
}

BaseModule* ModuleListItem::makeBlock()
{
    return BaseRegistry::createType(type);
}

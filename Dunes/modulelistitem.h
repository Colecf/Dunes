#ifndef MODULELISTITEM_H
#define MODULELISTITEM_H

#include <QString>

#include "QListWidgetItem"
#include "basemodule.h"

class ModuleListItem : public QListWidgetItem
{
public:
    ModuleListItem(QString title, QString desc, ModuleType t);
    QString getDescription();

    BaseModule* makeBlock();

private:
    QString description;
    ModuleType type;
};

#endif // MODULELISTITEM_H

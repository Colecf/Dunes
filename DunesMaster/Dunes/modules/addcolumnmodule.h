#ifndef ADDCOLUMNMODULE_H
#define ADDCOLUMNMODULE_H
#include "basemodule.h"
#include "QListWidget"
class AddColumnModule : public BaseModule
{
public:
    AddColumnModule();
    QString getCode();

    const static ModuleType type = ModuleAddColumn;

    const static QString title;
    const static QString description;
private:
};
#endif // ADDCOLUMNMODULE_H

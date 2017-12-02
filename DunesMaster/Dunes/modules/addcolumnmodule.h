#ifndef ADDCOLUMNMODULE_H
#define ADDCOLUMNMODULE_H
#include "basemodule.h"
#include "QListWidget"
class AddColumnModule : public BaseModule
{
public:
    AddColumnModule();
    QString getCode();
    QString getConfig(QString col);
    bool setConfig(QString variable, QString value);

    const static ModuleType type = ModuleAddColumn;

    const static QString title;
    const static QString description;
private:
};
#endif // ADDCOLUMNMODULE_H

#ifndef ADDROW_H
#define ADDROW_H
#include "basemodule.h"
#include "QListWidget"
class AddRowModule : public BaseModule
{
public:
    AddRowModule();

    const static ModuleType type = ModuleAddRow;

    const static QString title;
    const static QString description;
private:
};
#endif // ADDROW_H

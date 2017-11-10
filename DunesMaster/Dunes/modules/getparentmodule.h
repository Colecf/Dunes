#ifndef GETPARENTMODULE_H
#define GETPARENTMODULE_H
#include "basemodule.h"
#include "QListWidget"
class GetParentModule : public BaseModule
{
public:
    GetParentModule();

    const static ModuleType type = ModuleGetParent;

    const static QString title;
    const static QString description;
private:
};
#endif // GETPARENTMODULE_H

#ifndef SCOPE_H
#define SCOPE_H
#include <basemodule.h>
#include "QListWidget"
class ScopeModule : public BaseModule
{
public:
    ScopeModule();

    static void setUp(QListWidget*);
    const static ModuleType type = ModuleScope;

    const static QString title;
    const static QString description;
private:
};

#endif // SCOPE_H
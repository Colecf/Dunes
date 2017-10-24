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

private:
};

#endif // SCOPE_H

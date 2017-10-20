#ifndef SCOPE_H
#define SCOPE_H
#include <basemodule.h>

class Scope : public BaseModule
{
public:
    Scope();
private:
    static DerivedRegister<Scope> reg;
};

#endif // SCOPE_H

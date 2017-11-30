#ifndef NEXTMODULE_H
#define NEXTMODULE_H
#include "basemodule.h"
#include "QListWidget"
class NextModule : public BaseModule
{
public:
    NextModule();
    QString getCode();
    QString getConfig(QString col);

    const static ModuleType type = ModuleNext;

    const static QString title;
    const static QString description;
private:
};
#endif // NEXTMODULE_H

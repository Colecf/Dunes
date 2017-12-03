#ifndef FOREACHMODULE_H
#define FOREACHMODULE_H
#include "basemodule.h"
#include "QListWidget"
class ForEachModule : public BaseModule
{
public:
    ForEachModule();
    QString getCode();
    QString getConfig(QString col);
    bool setConfig(QString variable, QString value);

    const static ModuleType type = ModuleForEach;

    const static QString title;
    const static QString description;
private:
};
#endif // FOREACHMODULE_H

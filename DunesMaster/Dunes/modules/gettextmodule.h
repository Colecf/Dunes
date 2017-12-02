#ifndef GETTEXTMODULE_H
#define GETTEXTMODULE_H
#include "basemodule.h"
#include "QListWidget"
class GetTextModule : public BaseModule
{
public:
    GetTextModule();
    QString getCode();
    QString getConfig(QString col);
    bool setConfig(QString variable, QString value);

    const static ModuleType type = ModuleGetText;

    const static QString title;
    const static QString description;
private:
};

#endif // GETTEXTMODULE_H

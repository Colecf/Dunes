#ifndef SELECTMODULE_H
#define SELECTMODULE_H
#include "basemodule.h"
#include "QListWidget"
#include <QLineEdit>
class SelectModule : public BaseModule
{
public:
    SelectModule();
    QString getCode();
    QString getConfig(QString col);

    const static ModuleType type = ModuleSelect;

    const static QString title;
    const static QString description;

private:
    QLineEdit* SelectBox;

};
#endif // SELECTMODULE_H




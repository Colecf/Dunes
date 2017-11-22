#ifndef CONSTANTMODULE_H
#define CONSTANTMODULE_H
#include "basemodule.h"
#include "QListWidget"
#include <QLineEdit>
class ConstantModule : public BaseModule
{
public:
    ConstantModule();
    QString getCode();

    const static ModuleType type = ModuleConstant;

    const static QString title;
    const static QString description;

private:
    QLineEdit* SelectBox;

};
#endif // CONSTANTMODULE_H

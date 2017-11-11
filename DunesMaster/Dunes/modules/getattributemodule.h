#ifndef GETATTRIBUTEMODULE_H
#define GETATTRIBUTEMODULE_H
#include "basemodule.h"
#include "QListWidget"
#include <QLineEdit>
class GetAttributeModule : public BaseModule
{
public:
    GetAttributeModule();
    QString getCode();

    const static ModuleType type = ModuleGetAttribute;

    const static QString title;
    const static QString description;

private:
    QLineEdit* SelectBox;

};
#endif // GETATTRIBUTEMODULE_H

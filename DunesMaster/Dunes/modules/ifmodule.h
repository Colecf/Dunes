#ifndef IFMODULE_H
#define IFMODULE_H
#include "basemodule.h"
#include "QListWidget"
#include <QComboBox>
#include <QLineEdit>
class IfModule : public BaseModule
{
public:
    IfModule();
    QString getCode();

    const static ModuleType type = ModuleIf;

    const static QString title;
    const static QString description;

private:
    QLineEdit* operand;
    QComboBox* inputTypeDropDown;

};

#endif // IFMODULE_H

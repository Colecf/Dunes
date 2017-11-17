#ifndef WHILEMODULE_H
#define WHILEMODULE_H
#include "basemodule.h"
#include "QListWidget"
#include <QComboBox>
#include <QLineEdit>
class WhileModule : public BaseModule
{
public:
    WhileModule();
    QString getCode();

    const static ModuleType type = ModuleWhile;

    const static QString title;
    const static QString description;

private:
    QLineEdit* SelectBox;
    QComboBox* inputTypeDropDown;

};

#endif // WHILEMODULE_H

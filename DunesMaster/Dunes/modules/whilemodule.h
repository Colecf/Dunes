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
    QString getConfig(QString col);
    bool setConfig(QString variable, QString value);

    const static ModuleType type = ModuleWhile;

    const static QString title;
    const static QString description;

private:
    QLineEdit* operand;
    QComboBox* inputTypeDropDown;

};

#endif // WHILEMODULE_H

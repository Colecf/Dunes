#ifndef SETVARIABLEMODULE_H
#define SETVARIABLEMODULE_H

#include "basemodule.h"
#include "QListWidget"
#include <QComboBox>
#include <QLineEdit>

class SetVariableModule : public BaseModule
{
    Q_OBJECT

public:
    SetVariableModule();
    virtual ~SetVariableModule();
    QString getCode();
    QString getConfig(QString col);

    const static ModuleType type = ModuleSetVariable;

    const static QString title;
    const static QString description;

private:
    QLineEdit* varNameBox;
    QLabel* varNameLabel;
};

#endif // SETVARIABLEMODULE_H

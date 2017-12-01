#ifndef GETVARIABLEMODULE_H
#define GETVARIABLEMODULE_H

#include "basemodule.h"
#include "QListWidget"
#include <QComboBox>
#include <QLineEdit>

class GetVariableModule : public BaseModule
{
    Q_OBJECT

public:
    GetVariableModule();
    virtual ~GetVariableModule();
    QString getCode();
    QString getConfig(QString col);

    const static ModuleType type = ModuleGetVariable;

    const static QString title;
    const static QString description;

private:
    QLineEdit* varNameBox;
    QLabel* varNameLabel;
};

#endif // GETVARIABLEMODULE_H

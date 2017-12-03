#ifndef DOWNLOADMODULE_H
#define DOWNLOADMODULE_H
#include "../testcasespy.h"
#include "basemodule.h"
#include "QListWidget"
#include <QComboBox>
#include <QLineEdit>

class DownloadModule : public BaseModule
{
    Q_OBJECT

PUBLIC:
    DownloadModule();
    virtual ~DownloadModule();
    QString getCode();
    QString getConfig(QString col);
    bool setConfig(QString variable, QString value);

    const static ModuleType type = ModuleDL;

    const static QString title;
    const static QString description;

PRIVATE slots:
    void inputTypeChanged(int);

PRIVATE:
    QLineEdit* urlBox;
    QLabel* urlLabel;
    QComboBox* inputTypeDropDown;
};

#endif // DOWNLOADMODULE_H

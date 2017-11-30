#ifndef DOWNLOADMODULE_H
#define DOWNLOADMODULE_H

#include "basemodule.h"
#include "QListWidget"
#include <QComboBox>
#include <QLineEdit>

class DownloadModule : public BaseModule
{
    Q_OBJECT

public:
    DownloadModule();
    virtual ~DownloadModule();
    QString getCode();
    QString getConfig(QString col);

    const static ModuleType type = ModuleDL;

    const static QString title;
    const static QString description;

private slots:
    void inputTypeChanged(int);

private:
    QLineEdit* urlBox;
    QLabel* urlLabel;
    QComboBox* inputTypeDropDown;
};

#endif // DOWNLOADMODULE_H

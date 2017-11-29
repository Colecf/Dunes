#include <QDialog>
#include <QString>
#include <QVBoxLayout>

#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H


class OptionsMenu : public QDialog
{
    Q_OBJECT
public:
    OptionsMenu();
    QString getNodePath();
    QString getNpmPath();
private slots:
    void showOptions();
private:
    QVBoxLayout *layout;
    QString nodePath;
    QString npmPath;
};

#endif // OPTIONSMENU_H

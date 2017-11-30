#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "existingfiledialog.h"

#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H


class OptionsMenu : public QDialog
{
    Q_OBJECT
public:
    OptionsMenu();
    void setNpmPath(QString path);
    void setNodePath(QString path);
    QString getNodePath();
    QString getNpmPath();
private slots:
    void showOptions();
    void saveChanges();
private:
    QLabel *nodeLabel;
    ExistingFileDialog *nodeLineEdit;
    QLabel *npmLabel;
    ExistingFileDialog *npmLineEdit;
    QVBoxLayout *layout;
    QHBoxLayout *nodeLayout;
    QHBoxLayout *npmLayout;
    QString nodePath;
    QString npmPath;
};

#endif // OPTIONSMENU_H

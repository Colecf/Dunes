#ifndef CODEGEN_H
#define CODEGEN_H

#include <QGridLayout>
#include <QProcess>
#include <QMessageBox>
#include <QDir>
#include "optionsmenu.h"
#include "blockarea.h"


class CodeGen : public QObject
{
    Q_OBJECT
public:
    CodeGen();
    CodeGen(BlockArea *blockarea, OptionsMenu *optionsm);
private slots:
    void writeCode();
    void runCode();
    void finishedNodeProcess(int status);
    void finishedNpmProcess(int status);
    void finishNodeProcessError(QProcess::ProcessError error);
    void finishNpmProcessError(QProcess::ProcessError error);
private:
    QString generateCode();
    bool checkNodeAndNpmPaths();
    void startProcess(QString codePath, QString packageJsonPath);
    void setUpProcess(QString packageJsonPath, QString npmPath, QString nodePath);
    void setOutFiles(QDir curDir, QString folderPath, bool isNode);
    QString writePackageJson(QString codePath);
    QProcess *nodeProcess;
    QProcess *npmProcess;
    BlockArea *m_blockarea;
    OptionsMenu *options;
    QMessageBox *alert;
    static QString INITIAL_CODE;
};

#endif // CODEGEN_H

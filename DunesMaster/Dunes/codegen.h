#ifndef CODEGEN_H
#define CODEGEN_H

#include <QGridLayout>
#include <QProcess>
#include <QMessageBox>
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
    void finishProcessError(QProcess::ProcessError error);
private:
    QString generateCode();
    bool checkNodeAndNpmPaths();
    void startProcess(QString codePath, QString packageJsonPath);
    QString writePackageJson(QString codePath);
    QProcess *nodeProcess;
    QProcess *npmProcess;
    BlockArea *m_blockarea;
    OptionsMenu *options;
    QMessageBox *alert;
    static const QString INITIAL_CODE;
};

#endif // CODEGEN_H

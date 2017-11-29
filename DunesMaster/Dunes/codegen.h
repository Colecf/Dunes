#ifndef CODEGEN_H
#define CODEGEN_H

#include <QGridLayout>
#include <QProcess>
#include "blockarea.h"


class CodeGen : public QObject
{
    Q_OBJECT
public:
    CodeGen();
    CodeGen(BlockArea *blockarea);
private slots:
    void writeCode();
    void runCode();
    void finishProcess(int exitCode);
    void finishProcessError(QProcess::ProcessError error);
private:
    QString generateCode();
    void startProcess(QString codePath);
    void writePackageJson(QString codePath);
    BlockArea *m_blockarea;
    static const QString INITIAL_CODE;
};

#endif // CODEGEN_H

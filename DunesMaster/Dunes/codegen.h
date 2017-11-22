#ifndef CODEGEN_H
#define CODEGEN_H

#include <QGridLayout>
#include "blockarea.h"


class CodeGen : public QObject
{
    Q_OBJECT
public:
    CodeGen();
    CodeGen(BlockArea *blockarea);
private slots:
    void writeCode(QString filename = "dunes_index.js");
private:
    QString generateCode();
    BlockArea *m_blockarea;
};

#endif // CODEGEN_H

#ifndef SAVELOAD_H
#define SAVELOAD_H

#include <QObject>

#include <QGridLayout>
#include <QProcess>
#include "blockarea.h"

class SaveLoad : public QObject
{
    Q_OBJECT
public:
    SaveLoad();
    SaveLoad(BlockArea *blockarea);
public slots:
    void save();
    void load();
private:
    BlockArea *m_blockarea;
    QString genSaveData();
};

#endif // SAVELOAD_H

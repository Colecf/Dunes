#include "saveload.h"
#include <QDebug>
#include <QSaveFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>

SaveLoad::SaveLoad()
{

}

SaveLoad::SaveLoad(BlockArea *blockarea)
{
    m_blockarea = blockarea;
}

QString SaveLoad::genSaveData()
{
    QString saveData = "";
    auto rowToCol = m_blockarea->createRowToCol();
    QGridLayout *m_layout = m_blockarea->getLayout();
    for(int row = 0; row < m_layout->count(); row++){
        int col;
        if((col = m_blockarea->getCol(rowToCol, row)) == -1){
            qErrnoWarning("Error: col must integer >= 0");
            return NULL;
        }
        QWidget* const item = m_layout->itemAtPosition(row, col)->widget();
        if(BaseModule *module = dynamic_cast<BaseModule*>(item)) {
            saveData += module->getConfig(QString::number(col));
        }
    }
    return saveData;
}

void SaveLoad::save()
{
    QString data = genSaveData();
    QString pathToSave = QFileDialog::getSaveFileName(m_blockarea, tr("Save to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("Dunes Data (*.dunes)"));
    QSaveFile qSaveFile(pathToSave);
    if(qSaveFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&qSaveFile);
        stream << data;
        qSaveFile.commit();
        qInfo() << "saved dunes data to: " << pathToSave << endl;
    }
}

void SaveLoad::load()
{

}

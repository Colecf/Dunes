#include "saveload.h"
#include <QDebug>
#include <QSaveFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QRegularExpression>

SaveLoad::SaveLoad()
{

}

SaveLoad::SaveLoad(BlockArea *blockarea)
{
    m_blockarea = blockarea;
}

// Loops over each block in the layout and writes its configuration to a line
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
    QString pathToSave = QFileDialog::getSaveFileName(m_blockarea,
        tr("Save to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        tr("Dunes Project (*.dunes);;All Files (*)"));
    QSaveFile qSaveFile(pathToSave);
    if(qSaveFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&qSaveFile);
        stream << data;
        qSaveFile.commit();
        qInfo() << "saved dunes project to: " << pathToSave << endl;
    }
}

void SaveLoad::load()
{
    QString fileName = QFileDialog::getOpenFileName(m_blockarea,
        tr("Open Dunes Project"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        tr("Dunes Project (*.dunes);;All Files (*)"));
    if(fileName.isEmpty()) {
        return;
    }
    else {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QRegularExpression re("((\\w+)=(.*?))*;");
            QString data = "";
            QTextStream in(&file);
            // Loop through each line in the file
            while(!in.atEnd()) {
                BaseModule* module = nullptr;
                data = in.readLine();
                qInfo() << data << endl;
                QRegularExpressionMatchIterator matchIter = re.globalMatch(data);
                // Loop through all matches on the line
                while(matchIter.hasNext()) {
                    QRegularExpressionMatch match = matchIter.next();
                    // Type is assumed to be the first match
                    if(match.captured(2) == "type") {
                        // Skip over the next match, column, create the block
                        QRegularExpressionMatch colMatch = matchIter.next();
                        module = m_blockarea->createBlock((ModuleType)match.captured(3).toInt(), colMatch.captured(3).toInt());
                    } else {
                        // Every match after column is an option to be configured
                        if (module != nullptr) {
                            module->setConfig(match.captured(2), match.captured(3));
                        }
                    }
                }
            }
            file.close();
        }
    }
}

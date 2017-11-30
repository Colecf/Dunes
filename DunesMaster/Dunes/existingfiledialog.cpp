#include <QStandardPaths>
#include <QFileDialog>
#include "existingfiledialog.h"

ExistingFileDialog::ExistingFileDialog()
{
    this->setReadOnly(true);
}

void ExistingFileDialog::mouseReleaseEvent(QMouseEvent *){
    QString path = QFileDialog::getOpenFileName(NULL, tr("Select a file"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    if(path.size() != 0){
        this->setText(path);
    }
}

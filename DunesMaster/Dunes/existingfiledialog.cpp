#include <QStandardPaths>
#include <QFileDialog>
#include "existingfiledialog.h"

/*
    Read only, so the user must click on the line edit.
*/
ExistingFileDialog::ExistingFileDialog()
{
    this->setReadOnly(true);
}

/*
    On clicking this object, a FileDialog opens. The result of the file dialog is set to the text of this line edit.
*/
void ExistingFileDialog::mouseReleaseEvent(QMouseEvent *){
    QString path = QFileDialog::getOpenFileName(NULL, tr("Select a file"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    if(path.size() != 0){
        this->setText(path);
    }
}

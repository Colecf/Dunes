#include <QDialogButtonBox>
#include "optionsmenu.h"

OptionsMenu::OptionsMenu()
{
    nodePath = "";
    npmPath = "";
    layout = new QVBoxLayout();
    this->setLayout(layout);
    this->setModal(true);
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void OptionsMenu::showOptions(){
    this->show();
}

QString OptionsMenu::getNodePath(){
    return nodePath;
}

QString OptionsMenu::getNpmPath(){
    return npmPath;
}

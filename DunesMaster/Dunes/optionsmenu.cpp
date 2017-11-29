#include <QDialogButtonBox>
#include <QDebug>
#include "optionsmenu.h"

OptionsMenu::OptionsMenu()
{
    nodePath = "";
    npmPath = "";
    layout = new QVBoxLayout();
    nodeLayout = new QHBoxLayout();
    npmLayout = new QHBoxLayout();
    this->setLayout(layout);
    this->setModal(true);
    nodeLabel = new QLabel("Node Path:");
    npmLabel = new QLabel("NPM Path: ");
    nodeLineEdit = new QLineEdit();
    npmLineEdit = new QLineEdit();
    nodeLayout->addWidget(nodeLabel);
    nodeLayout->addWidget(nodeLineEdit);
    npmLayout->addWidget(npmLabel);
    npmLayout->addWidget(npmLineEdit);
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    layout->addLayout(nodeLayout);
    layout->addLayout(npmLayout);
    layout->addWidget(buttons);
    connect(buttons, SIGNAL(accepted()), this, SLOT(saveChanges()));
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void OptionsMenu::showOptions(){
    this->show();
}

void OptionsMenu::saveChanges(){
    setNodePath(nodeLineEdit->text());
    setNpmPath(npmLineEdit->text());
    qInfo() << "node path is: " << nodePath;
    qInfo() << "npm path is: " << npmPath;
    this->done(0);
}

void OptionsMenu::setNodePath(QString path){
    nodeLineEdit->setText(path);
    nodePath = path;
}

void OptionsMenu::setNpmPath(QString path){
    npmLineEdit->setText(path);
    npmPath = path;
}

QString OptionsMenu::getNodePath(){
    return nodePath;
}

QString OptionsMenu::getNpmPath(){
    return npmPath;
}

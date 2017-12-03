#include <QDialogButtonBox>
#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include "optionsmenu.h"

/*
    Sets up the layout for the OptionsMenu. Inherits from QDialog.
    Sets a vertical layout, then for the node and npm label and line edits, a horizontal layout.
    Adds the label, line edit to respective layouts. Adds save and cancel buttons, and sets the connection
    for both buttons.
*/
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
    nodeLineEdit = new ExistingFileDialog();
    npmLineEdit = new ExistingFileDialog();
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

/*
    Called on clicking the Options button. Shows this dialog.
*/
void OptionsMenu::showOptions(){
    this->show();
}

/*
    Called on clicking the Ok button. Saves the paths set in the line edits, and closes the dialog.
*/
void OptionsMenu::saveChanges(){
    setNodePath(nodeLineEdit->text());
    setNpmPath(npmLineEdit->text());
    qInfo() << "node path is: " << nodePath;
    qInfo() << "npm path is: " << npmPath;
    this->done(0);
}

/*
    Sets the line edit's text to path, and sets nodePath to path.
*/
void OptionsMenu::setNodePath(QString path){
    nodeLineEdit->setText(path);
    nodePath = path;
}

/*
    Sets the line edit's text to path, and sets nodePath to path.
*/
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

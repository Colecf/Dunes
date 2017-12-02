#include "setvariablemodule.h"
#include <QLabel>
#include <QLineEdit>

const QString SetVariableModule::title = "Set Variable";
const QString SetVariableModule::description = "Saves the current input stream into a global variable with a certain name. Use Get Variable to retreive it.";

SetVariableModule::SetVariableModule()
{
    m_titleLabel->setText(title);
    QGridLayout* optionsLayout = new QGridLayout();
    optionsLayout->setAlignment(Qt::AlignTop);
    varNameLabel = new QLabel("Variable name:");
    varNameBox = new QLineEdit();
    optionsLayout->addWidget(varNameLabel, 0, 0);
    optionsLayout->addWidget(varNameBox, 0, 1);

    m_optionsPanel->setLayout(optionsLayout);
}

SetVariableModule::~SetVariableModule()
{

}

QString SetVariableModule::getCode(){
    if(varNameBox->text().length() == 0) {
        return COMPILE_ERROR;
    }
    return "variables[\""+escapeString(varNameBox->text())+"\"] = top();\n";
}

QString SetVariableModule::getConfig(QString col){
    return "type=" + QString::number(type) + ";" + "col=" + col + ";name="+varNameBox->text() + ";\n";
}

bool SetVariableModule::setConfig(QString variable, QString value) {
    if (variable == "name") {
        varNameBox->setText(value);
        return true;
    } else {
        qInfo() << "Can't parse data: var: " << variable << "val: " << value << endl;
        return false;
    }
}

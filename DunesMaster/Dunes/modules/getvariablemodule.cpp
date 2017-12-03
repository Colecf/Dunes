#include "getvariablemodule.h"
#include <QLabel>
#include <QLineEdit>

const QString GetVariableModule::title = "Get Variable";
const QString GetVariableModule::description = "Replaces the current input stream with the contents of a variable. Use Set Variable to set the variable.";

GetVariableModule::GetVariableModule()
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

GetVariableModule::~GetVariableModule()
{

}

QString GetVariableModule::getCode(){
    if(varNameBox->text().length() == 0) {
        return COMPILE_ERROR;
    }
    return "load_variable(\""+escapeString(varNameBox->text())+"\");\n";
}

QString GetVariableModule::getConfig(QString col){
    return "type=" + QString::number(type) + ";" + "col=" + col + ";name="+varNameBox->text() + ";\n";
}

bool GetVariableModule::setConfig(QString variable, QString value) {
    if (variable == "name") {
        varNameBox->setText(value);
        return true;
    } else {
        qInfo() << "Can't parse data: var: " << variable << "val: " << value << endl;
        return false;
    }
}

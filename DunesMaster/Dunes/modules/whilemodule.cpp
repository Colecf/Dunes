#include "whilemodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

const QString WhileModule::title = "While";
const QString WhileModule::description = "Loops over the indented blocks below it while the condition is true.";

WhileModule::WhileModule()
{
    m_titleLabel->setText(title);
    QLabel* inputTypeLabel1 = new QLabel("Comparison type:");
    inputTypeDropDown = new QComboBox();
    inputTypeDropDown->insertItem(0, "==");
    inputTypeDropDown->insertItem(1, "!=");
    inputTypeDropDown->insertItem(2, "<");
    inputTypeDropDown->insertItem(3, ">");
    inputTypeDropDown->insertItem(4, "<=");
    inputTypeDropDown->insertItem(5, ">=");
    inputTypeDropDown->insertItem(6, "Contains");
    inputTypeDropDown->setCurrentIndex(0);
    QLabel* inputTypeLabel2 = new QLabel("Operand:");
    QGridLayout* optionsLayout = new QGridLayout();
    optionsLayout->setAlignment(Qt::AlignTop);
    optionsLayout->addWidget(inputTypeLabel1, 0, 0);
    optionsLayout->addWidget(inputTypeLabel2, 1, 0);
    optionsLayout->addWidget(inputTypeDropDown, 0, 1);

    operand = new QLineEdit();
    optionsLayout->addWidget(operand, 1, 1);

    m_optionsPanel->setLayout(optionsLayout);


}

QString WhileModule::getCode(){
    if(operand->text().length() == 0) {
        return COMPILE_ERROR;
    }
    QString code;
    if(inputTypeDropDown->currentIndex() == CONTAINSINDEX) {
        code = "while(top().indexOf(\""+escapeString(operand->text())+"\") != -1) {\n";
    } else {
        code = "while(top() " + inputTypeDropDown->currentText() + " '" + escapeString(operand->text()) + "') {\n";
    }
    if(this->children != NULL){
        for(size_t i = 0; i < this->children->size(); i++){
            code += "  " + this->children->at(i)->getCode();
        }
    }
    code += "}\n";
    return code;
}

QString WhileModule::getConfig(QString col){
    return "type=" + QString::number(type) + ";" + "col=" + col + ";" + "inputTypeDropDown=" + QString::number(inputTypeDropDown->currentIndex()) + ";Operand=" + operand->text() + "\n";
}


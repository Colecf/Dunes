#include "whilemodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

#define EQINDEX 0
#define NEINDEX 1
#define LTINDEX 2
#define GTINDEX 3
#define LEINDEX 4
#define GEINDEX 5
#define CONTAINSINDEX 6

const QString WhileModule::title = "While";
const QString WhileModule::description = "Loops over the indented blocks below it while the condition is true.";

WhileModule::WhileModule()
{
    m_titleLabel->setText(title);
    QLabel* inputTypeLabel1 = new QLabel("Comparison type:");
    inputTypeDropDown = new QComboBox();
    inputTypeDropDown->insertItem(EQINDEX, "==");
    inputTypeDropDown->insertItem(NEINDEX, "!=");
    inputTypeDropDown->insertItem(LTINDEX, "<");
    inputTypeDropDown->insertItem(GTINDEX, ">");
    inputTypeDropDown->insertItem(LEINDEX, "<=");
    inputTypeDropDown->insertItem(GEINDEX, ">=");
    inputTypeDropDown->insertItem(CONTAINSINDEX, "Contains");
    inputTypeDropDown->setCurrentIndex(EQINDEX);
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
        code = "while(top() " + inputTypeDropDown->currentText() + " \"" + escapeString(operand->text()) + "\") {\n";
    }
    for(size_t i = 0; i < children.size(); i++){
        code += "  " + children.at(i)->getCode();
    }
    code += "}\n";
    return code;
}

QString WhileModule::getConfig(QString col){
    return "type=" + QString::number(type) + ";" + "col=" + col + ";" + "inputTypeDropDown=" + QString::number(inputTypeDropDown->currentIndex()) + ";Operand=" + operand->text() + "\n";
}


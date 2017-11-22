#include "ifmodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

const QString IfModule::title = "If";
const QString IfModule::description = "Allows branching code based on the contents of the input stream. It does not edit the input stream.";

IfModule::IfModule()
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

    SelectBox = new QLineEdit();
    optionsLayout->addWidget(SelectBox, 1, 1);

    m_optionsPanel->setLayout(optionsLayout);


}

QString IfModule::getCode(){
    if(SelectBox->text().length() == 0) {
        return COMPILE_ERROR;
    }
    return "select("+SelectBox->text()+")";
}

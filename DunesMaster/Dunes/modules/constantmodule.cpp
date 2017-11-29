#include "constantmodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

const QString ConstantModule::title = "Constant";
const QString ConstantModule::description = "Replaces the input stream with a constant value.";

ConstantModule::ConstantModule()
{
    m_titleLabel->setText(title);
    QLabel* inputTypeLabel = new QLabel("Value:");
    QGridLayout* optionsLayout = new QGridLayout();
    optionsLayout->setAlignment(Qt::AlignTop);
    optionsLayout->addWidget(inputTypeLabel, 0, 0);
    m_optionsPanel->setLayout(optionsLayout);

    SelectBox = new QLineEdit();
    optionsLayout->addWidget(SelectBox, 0, 1);

}

QString ConstantModule::getCode(){
    if(SelectBox->text().length() == 0) {
        return COMPILE_ERROR;
    }
    return "constant('"+SelectBox->text()+"');\n";
}

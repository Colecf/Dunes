#include "getattributemodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

const QString GetAttributeModule::title = "GetAttribute";
const QString GetAttributeModule::description = "GetAttribute Description";

GetAttributeModule::GetAttributeModule()
{
    m_titleLabel->setText(title);
    QLabel* inputTypeLabel = new QLabel("Attribute:");
    QGridLayout* optionsLayout = new QGridLayout();
    optionsLayout->setAlignment(Qt::AlignTop);
    optionsLayout->addWidget(inputTypeLabel, 0, 0);
    m_optionsPanel->setLayout(optionsLayout);

    SelectBox = new QLineEdit();
    optionsLayout->addWidget(SelectBox, 0, 1);

}

QString GetAttributeModule::getCode(){
    return "boilerplateselect()";
}
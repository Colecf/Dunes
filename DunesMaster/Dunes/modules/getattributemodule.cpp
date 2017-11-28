#include "getattributemodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

const QString GetAttributeModule::title = "GetAttribute";
const QString GetAttributeModule::description = "Gets an HTML attribute from the first element in the input stream. The value of the attribute will go to the input stream.";

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
    if(SelectBox->text().length() == 0) {
        return COMPILE_ERROR;
    }
    return "attribute("+SelectBox->text()+");\n";
}

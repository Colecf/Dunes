#include "selectmodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

const QString SelectModule::title = "Select";
const QString SelectModule::description = "Narrows the input stream to the result of running a CSS selector on it.";

SelectModule::SelectModule()
{
    m_titleLabel->setText(title);
    QLabel* inputTypeLabel = new QLabel("CSS Selector:");
    QGridLayout* optionsLayout = new QGridLayout();
    optionsLayout->setAlignment(Qt::AlignTop);
    optionsLayout->addWidget(inputTypeLabel, 0, 0);
    m_optionsPanel->setLayout(optionsLayout);

    SelectBox = new QLineEdit();
    optionsLayout->addWidget(SelectBox, 0, 1);

}

QString SelectModule::getCode(){
    if(SelectBox->text().length() == 0) {
        return COMPILE_ERROR;
    }
    return "select_by_css(top(),'"+SelectBox->text()+"');\n";
}

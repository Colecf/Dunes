#include "downloadmodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

const QString DownloadModule::title = "Download";
const QString DownloadModule::description = "Download Description";

DownloadModule::DownloadModule()
{
    m_titleLabel->setText(title);
    QLabel* inputTypeLabel = new QLabel("Input type:");
    inputTypeDropDown = new QComboBox();
    inputTypeDropDown->insertItem(0, "None");
    inputTypeDropDown->insertItem(1, "URL");
    inputTypeDropDown->insertItem(2, "POST data");
    inputTypeDropDown->setCurrentIndex(1);
    QGridLayout* optionsLayout = new QGridLayout();
    optionsLayout->setAlignment(Qt::AlignTop);
    optionsLayout->addWidget(inputTypeLabel, 0, 0);
    optionsLayout->addWidget(inputTypeDropDown, 0, 1);

    urlBox = new QLineEdit();
    //urlBox->setMaximumWidth(100);
    urlLabel = new QLabel("URL: ");

    urlBox->setHidden(true);
    urlLabel->setHidden(true);

    optionsLayout->addWidget(urlLabel, 1, 0);
    optionsLayout->addWidget(urlBox, 1, 1);

    connect(inputTypeDropDown, SIGNAL(currentIndexChanged(int)), this, SLOT(inputTypeChanged(int)));

    m_optionsPanel->setLayout(optionsLayout);
}

DownloadModule::~DownloadModule()
{

}

void DownloadModule::inputTypeChanged(int slot)
{
    if(slot != 1)
    {
        urlBox->setHidden(false);
        urlLabel->setHidden(false);
    }
    else
    {
        urlBox->setHidden(true);
        urlLabel->setHidden(true);
    }
}

QString DownloadModule::getCode(){
    return "get_page(top());\n";
}

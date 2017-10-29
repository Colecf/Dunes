#include "downloadmodule.h"
#include "modulelistitem.h"
#include <QLabel>
#include <QComboBox>

const QString DownloadModule::title = "Download";
const QString DownloadModule::description = "Download Description";

DownloadModule::DownloadModule()
{
    m_titleLabel->setText(title);
    QLabel* inputTypeLabel = new QLabel("Input type:");
    QComboBox* inputTypeDropDown = new QComboBox();
    inputTypeDropDown->insertItem(0, "None");
    inputTypeDropDown->insertItem(1, "URL");
    inputTypeDropDown->insertItem(2, "POST data");
    QGridLayout* optionsLayout = new QGridLayout();
    optionsLayout->setAlignment(Qt::AlignTop);
    optionsLayout->addWidget(inputTypeLabel);
    optionsLayout->addWidget(inputTypeDropDown);

    m_optionsPanel->setLayout(optionsLayout);
}

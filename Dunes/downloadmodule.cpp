#include "downloadmodule.h"
#include "modulelistitem.h"

const QString DownloadModule::title = "Download";
const QString DownloadModule::description = "Download Description";

DownloadModule::DownloadModule()
{
    m_titleLabel->setText(title);
}

#include "downloadmodule.h"
#include "modulelistitem.h"

const QString DownloadModule::title = "Download";
const QString DownloadModule::description = "Download Description";

DownloadModule::DownloadModule()
{
    setText("Download");
}


void DownloadModule::setUp(QListWidget* list)
{
    ModuleListItem *listItem = new ModuleListItem(title, description, ModuleDL);
    list->addItem(listItem);

    BaseRegistry::registerType(ModuleDL, &createT<DownloadModule>);
}

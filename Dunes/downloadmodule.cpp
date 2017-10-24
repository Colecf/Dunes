#include "downloadmodule.h"
#include "modulelistitem.h"
DownloadModule::DownloadModule()
{

}


void DownloadModule::setUp(QListWidget* list)
{
    ModuleListItem *listItem = new ModuleListItem(QString("Download"), QString("This is a download description"), ModuleDL);
    list->addItem(listItem);

    BaseRegistry::registerType(ModuleDL, &createT<DownloadModule>);
}

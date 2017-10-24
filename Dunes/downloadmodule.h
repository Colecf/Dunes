#ifndef DOWNLOADMODULE_H
#define DOWNLOADMODULE_H

#include "basemodule.h"
#include "QListWidget"

class DownloadModule : public BaseModule
{
public:
    DownloadModule();


    static void setUp(QListWidget*);

    const static ModuleType type = ModuleDL;

    const static QString title;
    const static QString description;
};

#endif // DOWNLOADMODULE_H

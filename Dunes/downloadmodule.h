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
};

#endif // DOWNLOADMODULE_H

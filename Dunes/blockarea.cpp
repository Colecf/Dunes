#include "blockarea.h"

BlockArea::BlockArea(QWidget *parent) : QWidget(parent)
{
}

bool BlockArea::createBlock(const QString &blockType)
{
    BaseModule* module = BaseRegistry::createInstance(blockType);
    module->setText(blockType);
    module->setParent(this);
    module->show();
    return 0;
}

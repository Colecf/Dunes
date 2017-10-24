#include "blockarea.h"

BlockArea::BlockArea(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    setLayout(m_layout);
}

bool BlockArea::createBlock(const QString &blockType)
{
    BaseModule* module = BaseRegistry::createInstance(blockType);
    module->setText(blockType);
    module->setParent(this);
    m_layout->addWidget(module);
    module->show();
    return 0;
}

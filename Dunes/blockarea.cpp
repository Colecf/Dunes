#include "blockarea.h"

BlockArea::BlockArea(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    //m_layout->setAlignment(Qt::AlignCenter);
    //setLayout(m_layout);
}

bool BlockArea::createBlock(ModuleType blockType)
{
    BaseModule* module = BaseRegistry::createInstance(blockType);
    module->setParent(this);
    m_layout->addWidget(module);
    //module->show();
    return 0;
}

QVBoxLayout* BlockArea::getLayout()
{
    return m_layout;
}

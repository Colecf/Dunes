#include "blockarea.h"

BlockArea::BlockArea(QWidget *parent) : QScrollArea(parent)
{
    QWidget* widget = new QWidget;
    m_layout = new QVBoxLayout;
    m_layout->setAlignment(Qt::AlignTop);
    widget->setLayout(m_layout);
    setWidget(widget);
    setWidgetResizable(true);
}

bool BlockArea::createBlock(ModuleType blockType)
{
    BaseModule* module = BaseRegistry::createInstance(blockType);
    m_layout->addWidget(module);
    return true;
}

QVBoxLayout* BlockArea::getLayout()
{
    return m_layout;
}

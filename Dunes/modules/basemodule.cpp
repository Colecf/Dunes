#include "basemodule.h"
#include "modulelistitem.h"

BaseRegistry::map_type BaseRegistry::map;

const QString BaseModule::title = "Base";
const QString BaseModule::description = "Description";
QWidget* BaseModule::mainWindow;

BaseModule::BaseModule()
{
    m_layout = new QGridLayout(this);
    m_titleLabel = new QLabel();
    m_titleLabel->setText("ERROR");
    m_layout->addWidget(m_titleLabel);
    setObjectName("BaseModule");
    setStyleSheet("#BaseModule { background-color: white; border: 3px solid grey; border-radius:20px; }");

    m_optionsPanel = new QWidget();
    m_optionsPanel->setObjectName("optionsPanel");
}

BaseModule::~BaseModule() {
    //TODO maybe delete title label and other widgets?
}

void BaseModule::mousePressEvent(QMouseEvent* event)
{
    //TODO change to using slots and signals to avoid global mainWindow
    if(event->button() == Qt::LeftButton)
    {
        BaseModule* selected = parent()->findChild<BaseModule*>("BaseModuleSelected");
        if(selected)
        {
            selected->setObjectName("BaseModule");
            selected->setStyleSheet("#BaseModule { background-color: white; border: 3px solid grey; border-radius:20px; }");
        }
        setStyleSheet("#BaseModule { background-color: white; border: 3px solid lightblue; border-radius:20px; }");
        setObjectName("BaseModuleSelected");

        QWidget* toRemove = mainWindow->findChild<QWidget*>("optionsPanel", Qt::FindDirectChildrenOnly);
        if(toRemove) {
            mainWindow->layout()->removeWidget(toRemove);
            toRemove->setParent(nullptr);
        }
        mainWindow->layout()->addWidget(m_optionsPanel);
        m_optionsPanel->setHidden(false);
    }
}

void BaseModule::createModuleListItem(QListWidget* list, QString title, QString description, ModuleType type) {
    list->addItem(new ModuleListItem(title, description, type));
}

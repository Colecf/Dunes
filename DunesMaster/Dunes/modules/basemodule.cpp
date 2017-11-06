#include "basemodule.h"
#include "modulelistitem.h"
#include "modulelist.h"
#include <QPainter>
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

/*  IN PROGRESS: INSERT FROM MODLIST INTO BLOCKAREA ANYWHERE
 * void BaseModule::dragEnterEvent(QDragEnterEvent *event)
{
    //if (event->mimeData()->hasFormat("text/plain"))
            event->acceptProposedAction();
}

void BaseModule::dropEvent(QDropEvent *event)
{
    //textBrowser->setPlainText(event->mimeData()->text());
    //mimeTypeCombo->clear();
   //mimeTypeCombo->addItems(event->mimeData()->formats());
   const QMimeData* itemData = event->mimeData();

    //qInfo() << event->mimeData()->text();
    //qInfo() << ((PassData*)test)->getQListWidgetItem()->text();
    QListWidgetItem *block = ((PassData*)itemData)->getQListWidgetItem();
    qInfo() << ((ModuleListItem*)block)->getType();
    createBlock((((ModuleListItem*)block)->getType()));
    event->acceptProposedAction();
}*/
void BaseModule::createModuleListItem(ModuleList* list, QString title, QString description, ModuleType type) {
    list->addItem(new ModuleListItem(title, description, type));
}

void BaseModule::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

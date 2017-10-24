#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloadmodule.h"
#include "modulelistitem.h"
#include "scopemodule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Initilize UI
    //Module list
    m_modList = new QListWidget(this);
    m_modList->resize(320, 360);

    DownloadModule::setUp(m_modList);
    ScopeModule::setUp(m_modList);

    //Description box
    m_desc = new QTextEdit("Click on a module to see its description!", this);
    m_desc->move(0, 360);
    m_desc->resize(320, 360);
    m_desc->setReadOnly(true);

    //Connects the module list with the description
    connect(m_modList, SIGNAL(itemSelectionChanged()), this, SLOT( updateDesc()));

    //Setting up description table on click change the description the new module description
    m_blockarea = new BlockArea(this);
    m_blockarea->move(320, 0);
    m_blockarea->resize(640, 540);
    //m_blockarea->createBlock("Scope");

    connect(m_modList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(makeBlock(QListWidgetItem*)));
}

void MainWindow::updateDesc()
{
   m_desc->setText(((ModuleListItem*)m_modList->currentItem())->getDescription());
}

void MainWindow::makeBlock(QListWidgetItem* blockItem)
{
    m_blockarea->createBlock(((ModuleListItem*)blockItem)->getType());
}

MainWindow::~MainWindow()
{
}

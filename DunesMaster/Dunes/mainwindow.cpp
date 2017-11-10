#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "modules/downloadmodule.h"
#include "modules/scopemodule.h"
#include "modules/selectmodule.h"
#include "modules/gettextmodule.h"
#include "modules/nextmodule.h"
#include "modules/addrowmodule.h"
#include "modules/addcolumnmodule.h"
#include "modules/getparentmodule.h"
#include "modulelistitem.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Initilize UI
    //Module list
    m_modList = new ModuleList(this);
   // m_modList->resize(320, 360);

    BaseModule::setUp<DownloadModule>(m_modList);
    BaseModule::setUp<ScopeModule>(m_modList);
    BaseModule::setUp<SelectModule>(m_modList);
    BaseModule::setUp<GetTextModule>(m_modList);
    BaseModule::setUp<NextModule>(m_modList);
    BaseModule::setUp<AddRowModule>(m_modList);
    BaseModule::setUp<AddColumnModule>(m_modList);
    BaseModule::setUp<GetParentModule>(m_modList);

    //Description box
    m_desc = new QTextEdit("Click on a module to see its description!");
    m_desc->setReadOnly(true);

    //Connects the module list with the description
    connect(m_modList, SIGNAL(itemSelectionChanged()), this, SLOT( updateDesc()));

    //Setting up block diagram area
    m_blockarea = new BlockArea(this);
    //m_blockarea->move(320, 0);
    //m_blockarea->resize(640, 540);
    //m_blockarea->createBlock("Scope");
   // m_blockarea->getLayout()->setAlignment(Qt::AlignLeft);

    //Layout System
    //Box is a layout that holds all layouts
    box = new QBoxLayout(QBoxLayout::LeftToRight);

    //Left layout. Module list + description
    left_layout = new QVBoxLayout();
    //m_modList->setSizePolicy(QSizePolicy::Minimum);
    left_layout->addWidget(m_modList);
    left_layout->addWidget(m_desc);
    left_layout->setAlignment(m_modList, Qt::AlignLeft);
    left_layout->setAlignment(m_desc, Qt::AlignLeft);

    //Configuration layout
    right_layout = new QWidget();
    right_layout->setObjectName("optionsPanel");
    box->addLayout(left_layout);
    box->addWidget(m_blockarea);
    box->addWidget(right_layout);


    //layout->setAlignment(m_blockarea->getLayout(), Qt::AlignHCenter);

    //this->setLayout(layout);
    //layout->setAlignment(m_blockarea, Qt::AlignCenter);

    QWidget *test = new QWidget(this);
    //test->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    this->setCentralWidget(test);
    test->setLayout(box);

    BaseModule::mainWindow = test;

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

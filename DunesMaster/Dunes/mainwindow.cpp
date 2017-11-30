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
#include "modules/foreachmodule.h"
#include "modules/getattributemodule.h"
#include "modules/ifmodule.h"
#include "modules/whilemodule.h"
#include "modules/constantmodule.h"
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
    BaseModule::setUp<ForEachModule>(m_modList);
    BaseModule::setUp<GetAttributeModule>(m_modList);
    BaseModule::setUp<IfModule>(m_modList);
    BaseModule::setUp<WhileModule>(m_modList);
    BaseModule::setUp<ConstantModule>(m_modList);

    //Description box
    m_desc = new QTextEdit("Click on a module to see its description!");
    m_desc->setReadOnly(true);

    //Connects the module list with the description
    connect(m_modList, SIGNAL(itemSelectionChanged()), this, SLOT( updateDesc()));

    //Setting up block diagram area
    m_blockarea = new BlockArea(this);

    //Layout System
    //completeContainer is a layout that holds all layouts
    box = new QBoxLayout(QBoxLayout::LeftToRight);
    createTopLayout();
    createCompleteContainer();

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
    test->setLayout(completeContainer);

    BaseModule::mainWindow = test;
    codeGen = new CodeGen(m_blockarea, options);
    connect(m_modList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(makeBlock(QListWidgetItem*)));
    connect(runButton, SIGNAL(released()), codeGen, SLOT(runCode()));
    connect(generateButton, SIGNAL(released()), codeGen, SLOT(writeCode()));
    connect(optionsButton, SIGNAL(released()), options, SLOT(showOptions()));
}

void MainWindow::updateDesc()
{
   m_desc->setText(((ModuleListItem*)m_modList->currentItem())->getDescription());
}

void MainWindow::makeBlock(QListWidgetItem* blockItem)
{
    m_blockarea->createBlock(((ModuleListItem*)blockItem)->getType());
}

void MainWindow::createTopLayout(){
    options = new OptionsMenu();
    top_layout = new QHBoxLayout();
    runButton = new QPushButton("Run Code");
    generateButton = new QPushButton("Generate");
    optionsButton = new QPushButton("Options");
    top_layout->addWidget(runButton);
    top_layout->addWidget(generateButton);
    top_layout->addWidget(optionsButton);
}

void MainWindow::createCompleteContainer(){
    completeContainer = new QVBoxLayout();
    completeContainer->addLayout(top_layout);
    completeContainer->addLayout(box);
}

MainWindow::~MainWindow()
{
}

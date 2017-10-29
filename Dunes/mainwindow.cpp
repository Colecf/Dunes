#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "downloadmodule.h"
#include "modulelistitem.h"
#include "scopemodule.h"
#include "basemodule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Initilize UI
    //Module list
    m_modList = new QListWidget();
   // m_modList->resize(320, 360);

    BaseModule::setUp<DownloadModule>(m_modList);
    BaseModule::setUp<ScopeModule>(m_modList);

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

    //Configuration panel change later
    QRadioButton *button = new QRadioButton();
    QRadioButton *button1 = new QRadioButton();
    button1->setText("testing");
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
    right_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    right_layout->addWidget(button);
    right_layout->addWidget(button1);
    right_layout->setAlignment(Qt::AlignTop);

    box->addLayout(left_layout);
    box->addLayout(m_blockarea->getLayout());
    box->setStretchFactor(m_blockarea->getLayout(), 2);
    box->addLayout(right_layout);
    //box->setStretchFactor(left_layout, 1);
    //box->setStretchFactor(right_layout, 0);

    //layout->setAlignment(m_blockarea->getLayout(), Qt::AlignHCenter);

    //this->setLayout(layout);
    //layout->setAlignment(m_blockarea, Qt::AlignCenter);

    QWidget *test = new QWidget(this);
    //test->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    this->setCentralWidget(test);
    test->setLayout(box);

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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Initilize UI
    //Module list
    m_modList = new QListWidget(this);
    m_modList->resize(320, 360);
    //Add item to list
    m_modList->addItem("Select something");
    m_modList->item(m_modList->count() - 1)->setToolTip("This is my description!");
    m_modList->addItem("LOOP");
    m_modList->item(m_modList->count() - 1)->setToolTip("This is a loop description");

    //Description box
    m_desc = new QTextEdit("Click on a module to see its description!", this);
    m_desc->move(0, 360);
    m_desc->resize(320, 360);
    m_desc->setReadOnly(true);

    m_tree = new QTreeWidget(this);
    m_tree->move(320, 0);
    m_tree->resize(640, 540);
    //columns index start at 0 like arrays.
    m_tree->setColumnCount(1);
    //Connects the module list with the description
    connect(m_modList, SIGNAL(itemSelectionChanged()), this, SLOT( update_desc()));

    //Connects module list with tree only on double click
    connect(m_modList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(update_tree()));

    //Remove item from tree by double clicking
    connect(m_tree, SIGNAL (itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(remove_entry_from_tree()));

    //Setting up description table on click change the description the new module description
}

void MainWindow::update_desc()
{
   m_desc->setText(m_modList->currentItem()->toolTip());
}

void MainWindow::update_tree()
{
    QTreeWidgetItem *new_tree_item = new QTreeWidgetItem();
    new_tree_item->setText(0, m_modList->currentItem()->text());
    m_tree->addTopLevelItem(new_tree_item);
    //stuff for proof of concept
    QTreeWidgetItem *child_tree_item = new QTreeWidgetItem();
    child_tree_item->setText(0, "child testing!!!");
    new_tree_item->addChild(child_tree_item);

    QTreeWidgetItem *child_tree_item1 = new QTreeWidgetItem();
    child_tree_item1->setText(0, "its me ur brother");
    new_tree_item->addChild(child_tree_item1);
    QTreeWidgetItem *great_child_tree_item = new QTreeWidgetItem();
    great_child_tree_item->setText(0, "young dude here");
    child_tree_item1->addChild(great_child_tree_item);

}
//delete entrys from tree
void MainWindow::remove_entry_from_tree()
{
    QTreeWidgetItem *cur = m_tree->currentItem();
    if(m_tree->currentItem()->parent() != NULL)
    {
        m_tree->currentItem()->parent()->removeChild(cur);
        free(cur);
    }
    else
    {
        delete(cur);
    }
}
MainWindow::~MainWindow()
{
}

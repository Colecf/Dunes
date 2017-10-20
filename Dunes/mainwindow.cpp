#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initilize UI
    //Module list
    mod_list = new QListWidget(this);
    mod_list->resize(320, 360);
    //Add item to list
    mod_list->addItem("Select something");
    mod_list->item(mod_list->count() - 1)->setToolTip("This is my description!");
    mod_list->addItem("LOOP");
    mod_list->item(mod_list->count() - 1)->setToolTip("This is a loop description");

    //Description box
    desc = new QTextEdit("Click on a module to see its description!", this);
    desc->move(0, 360);
    desc->resize(320, 360);
    desc->setReadOnly(true);

    tree = new QTreeWidget(this);
    tree->move(320, 0);
    tree->resize(640, 540);
    //columns index start at 0 like arrays.
    tree->setColumnCount(1);
    //Connects the module list with the description
    connect(mod_list, SIGNAL(itemSelectionChanged()), this, SLOT( update_desc()));

    //Connects module list with tree only on double click
    connect(mod_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(update_tree()));

    //Remove item from tree by double clicking
    connect(tree, SIGNAL (itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(remove_entry_from_tree()));

    //Setting up description table on click change the description the new module description


    //ui->setupUi(this);
}

void MainWindow::update_desc()
{
   desc->setText(mod_list->currentItem()->toolTip());
}

void MainWindow::update_tree()
{
    QStringList *cur_item = new QStringList(mod_list->currentItem()->text());

    QTreeWidgetItem *new_tree_item = new QTreeWidgetItem();
    new_tree_item->setText(0, mod_list->currentItem()->text());
    tree->addTopLevelItem(new_tree_item);
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
    QTreeWidgetItem *cur = tree->currentItem();
    if(tree->currentItem()->parent() != NULL)
    {
        tree->currentItem()->parent()->removeChild(cur);
        free(cur);
    }
    else
    {
        delete(cur);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

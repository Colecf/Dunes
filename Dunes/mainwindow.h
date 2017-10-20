#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void update_desc();
    void update_tree();
    void remove_entry_from_tree();
private:
    Ui::MainWindow *ui;
    QListWidget *mod_list;
    QTableWidget *desc_table;
    QTextEdit *desc;
    QTreeWidget *tree;
};

#endif // MAINWINDOW_H

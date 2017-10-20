#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QTreeWidget>

#include "basemodule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void initModule(BaseModule* module);

    ~MainWindow();
private slots:
    void update_desc();
    void update_tree();
    void remove_entry_from_tree();
private:
    QListWidget* m_modList;
    QTableWidget *m_descTable;
    QTextEdit *m_desc;
    QTreeWidget *m_tree;
};

#endif // MAINWINDOW_H

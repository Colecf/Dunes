#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDebug>
#include <QListWidget>

#include "blockarea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
private slots:
    void updateDesc();
    void makeBlock(QListWidgetItem* blockItem);

private:
    QListWidget* m_modList;
    QTextEdit *m_desc;
    BlockArea *m_blockarea;
};

#endif // MAINWINDOW_H

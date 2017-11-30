#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDebug>
#include <QListWidget>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QRadioButton>
#include "modulelist.h"
#include "blockarea.h"
#include "codegen.h"
#include "optionsmenu.h"
#include "saveload.h"

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
    void createTopLayout();
    void createCompleteContainer();

    ModuleList* m_modList;
    QTextEdit *m_desc;
    BlockArea *m_blockarea;
    QVBoxLayout *left_layout;
    QWidget *right_layout;
    QBoxLayout *box;
    QHBoxLayout *top_layout;
    QVBoxLayout *completeContainer;
    QPushButton *runButton;
    QPushButton *generateButton;
    QPushButton *optionsButton;
    CodeGen *codeGen;
    OptionsMenu *options;
    QPushButton *saveButton;
    QPushButton *loadButton;
    SaveLoad *saveLoad;
};

#endif // MAINWINDOW_H

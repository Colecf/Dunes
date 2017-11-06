#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.resize(1280, 720);
    window.show();
    return a.exec();
}



#ifndef MODULELIST_H
#define MODULELIST_H
#include <QWidget>
#include <QListWidget>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>
#include <QApplication>

class ModuleList : public QListWidget
{
    Q_OBJECT
public:
    explicit ModuleList(QWidget *parent = nullptr);
    QPoint dragStartPosition;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};
#endif

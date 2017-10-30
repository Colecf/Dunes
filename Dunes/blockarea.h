#ifndef BLOCKAREA_H
#define BLOCKAREA_H
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QDrag>
#include <QMimeData>
#include <QListWidgetItem>
#include "modulelistitem.h"
#include "modules/basemodule.h"
#include "modulelist.h"
class BlockArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit BlockArea(QWidget *parent = nullptr);
    bool createBlock(ModuleType);
    QVBoxLayout* getLayout();
private:
    QVBoxLayout* m_layout;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // BLOCKAREA_H

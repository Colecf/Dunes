#ifndef BLOCKAREA_H
#define BLOCKAREA_H
#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDrag>
#include <QMimeData>
#include <QListWidgetItem>
#include "modulelistitem.h"
#include "modules/basemodule.h"
#include "modules/scopemodule.h"
#include "modulelist.h"
class BlockArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit BlockArea(QWidget *parent = nullptr);
    bool createBlock(ModuleType);
    QGridLayout* getLayout();

private slots:
    void keyPressedInModule(BaseModule* mod, QKeyEvent* event);

private:
    QGridLayout* m_layout;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // BLOCKAREA_H

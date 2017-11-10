#ifndef BLOCKAREA_H
#define BLOCKAREA_H
#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDrag>
#include <QMimeData>
#include <QListWidgetItem>
#include <unordered_map>
#include "modulelistitem.h"
#include "modules/basemodule.h"
#include "modules/scopemodule.h"
#include "modules/selectmodule.h"
#include "modules/gettextmodule.h"
#include "modules/nextmodule.h"
#include "modules/addrowmodule.h"
#include "modules/addcolumnmodule.h"
#include "modules/getparentmodule.h"
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
    void generateCode();
private:
    QGridLayout* m_layout;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    int getCol(const std::unordered_map<int, int> *dict, int row);
};

#endif // BLOCKAREA_H

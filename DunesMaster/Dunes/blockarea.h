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
#include <QFrame>
#include "modulelistitem.h"
#include "modules/basemodule.h"
#include "modules/scopemodule.h"
#include "modules/selectmodule.h"
#include "modules/gettextmodule.h"
#include "modules/nextmodule.h"
#include "modules/addrowmodule.h"
#include "modules/addcolumnmodule.h"
#include "modules/getparentmodule.h"
#include "modules/foreachmodule.h"
#include "modules/getattributemodule.h"
#include "modules/ifmodule.h"
#include "modules/whilemodule.h"
#include "modules/constantmodule.h"
class BlockArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit BlockArea(QWidget *parent = nullptr);
    bool createBlock(ModuleType);
    bool createBlockAt(ModuleType blockType, int module_location);
    void moveBlocksDown(int module_location);
    void moveBlocksDownUntil(int start, int end);
    void moveBlocksUp(int start, int end);
    QGridLayout* getLayout();
    std::unordered_map<int, int>* createRowToCol();
    int getCol(const std::unordered_map<int, int> *dict, int row);
private slots:
    void keyPressedInModule(BaseModule* mod, QKeyEvent* event);
private:
    QGridLayout* m_layout;
    int mouseCoordToModuleLocation(int yCoord);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    int cur_line_location = -1;
    QFrame *line = nullptr;
    //void paintEvent(QPaintEvent *event);

};

#endif // BLOCKAREA_H

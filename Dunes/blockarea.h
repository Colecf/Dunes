#ifndef BLOCKAREA_H
#define BLOCKAREA_H
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

#include "basemodule.h"

class BlockArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit BlockArea(QWidget *parent = nullptr);
    bool createBlock(ModuleType);
    QVBoxLayout* getLayout();
private:
    QVBoxLayout* m_layout;
};

#endif // BLOCKAREA_H

#ifndef BLOCKAREA_H
#define BLOCKAREA_H
#include<string>
#include<QWidget>
#include <QVBoxLayout>

#include "basemodule.h"

class BlockArea : public QWidget
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

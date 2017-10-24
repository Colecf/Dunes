#ifndef BLOCKAREA_H
#define BLOCKAREA_H
#include<string>
#include<QWidget>

#include <basemodule.h>

class BlockArea : public QWidget
{
    Q_OBJECT
public:
    explicit BlockArea(QWidget *parent = nullptr);
    bool createBlock(const QString &);

signals:
};

#endif // BLOCKAREA_H

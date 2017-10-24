#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <QListWidget>

class BlockList : public QListWidget
{

public:
    BlockList(QWidget *parent = nullptr);
    enum Blocks { Scope, Select };
    Q_ENUM(Blocks)
};

#endif // BLOCKLIST_H

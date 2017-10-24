#include "blocklist.h"

BlockList::BlockList(QWidget *parent) : QListWidget(parent)
{
    QListWidgetItem* blockItem = new QListWidgetItem();
    blockItem->setText("Scope");
    QVariant type = qVariantFromValue(Blocks::Scope);
    blockItem->setData(Qt::UserRole, type);
    addItem(blockItem);

    item(count() - 1)->setToolTip("Scope placeholder description");
}

#include <QListWidget>
#include <QListWidgetItem>
#include <QMimeData>

class PassData : public QMimeData
{
    Q_OBJECT
public:
    explicit PassData();
    void setQListWidgetItem(QListWidget *list);
    QListWidgetItem* getQListWidgetItem();
    void setIndex(int index);
    int getIndex();
    void setHeight(int new_height);
    int getHeight();
private:
    QListWidgetItem* widget_item;
    int idx;
    int height;
};

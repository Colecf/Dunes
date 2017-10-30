#include <QListWidget>
#include <QListWidgetItem>
#include <QMimeData>

class PassData : public QMimeData
{
    Q_OBJECT
public:
    explicit PassData(QObject *parent = nullptr);
    void setQListWidgetItem(QListWidget *list);
    QListWidgetItem* getQListWidgetItem();
private:
    QListWidgetItem* widget_item;

};

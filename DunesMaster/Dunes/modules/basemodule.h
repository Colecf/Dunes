#ifndef BASEMODULE_H
#define BASEMODULE_H
#include <map>
#include <string>
#include <QString>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QBoxLayout>
#include "../modulelist.h"
enum ModuleType {
    ModuleError,
    ModuleDL,
    ModuleSelect,
    ModuleScope,
    ModuleGetText,
    ModuleNext,
    ModuleAddRow,
    ModuleAddColumn,
    ModuleGetParent,
};

class BaseModule;

template<typename T> BaseModule* createT() { return new T; }

class BaseRegistry
{
    using map_type = std::map<ModuleType, BaseModule*(*)()>;
public:
    static void registerType(ModuleType t, BaseModule* (*creationFunc)()) {
        map.insert(std::make_pair(t, creationFunc));
    }
    static BaseModule* createInstance(ModuleType t) {
        if(map.count(t) > 0) {
            return map.at(t)();
        }
        return nullptr;
    }

private:
    static map_type map;
};

class BaseModule : public QWidget
{
    Q_OBJECT

public:
    BaseModule();
    virtual ~BaseModule();

    virtual void mousePressEvent(QMouseEvent*) override;
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dropEvent(QDropEvent *event);

    // Sets up the module list item
    // templated static functions must be defined in the header, but to prevent
    // a circular header inclusion I implmented createModuleListItem in the cpp
    template<typename T> static void setUp(ModuleList* list) {
        createModuleListItem(list, T::title, T::description, T::type);
        BaseRegistry::registerType(T::type, &createT<T>);
    }
    const static ModuleType type = ModuleError;
    const static QString title;
    const static QString description;
    static QWidget* mainWindow;

    // Disables switching focus when hitting tab when the focus is on a module
    bool focusNextPrevChild(bool) override { return false; }

signals:
    void keyPressed(BaseModule*, QKeyEvent*);

protected:
    void keyPressEvent(QKeyEvent *) override;

    QLabel* m_titleLabel;
    QGridLayout* m_layout;
    QWidget* m_optionsPanel;
private:
    void paintEvent(QPaintEvent *) override;
    static void createModuleListItem(ModuleList* list, QString title, QString description, ModuleType type);
};

#endif // BASEMODULE_H

#ifndef BASEMODULE_H
#define BASEMODULE_H
#include <map>
#include <string>
#include <QString>
#include <QPushButton>

enum ModuleType {
    ModuleError,
    ModuleDL,
    ModuleSelect,
    ModuleScope
};

class BaseModule : public QPushButton
{
public:

    const static ModuleType type = ModuleError;
    const static QString title;
    const static QString description;
private:
};

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

#endif // BASEMODULE_H

#ifndef BASEMODULE_H
#define BASEMODULE_H
#include <map>
#include <string>

enum ModuleType {
    ModuleError,
    ModuleDL,
    ModuleSelect,
    ModuleScope
};

class BaseModule
{
public:

    const static ModuleType type = ModuleError;

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
    static BaseModule* createType(ModuleType t) {
        if(map.count(t) > 0) {
            return map.at(t)();
        }
        return nullptr;
    }

private:
    static map_type map;
};

#endif // BASEMODULE_H

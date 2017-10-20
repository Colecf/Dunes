#ifndef BASEMODULE_H
#define BASEMODULE_H
#include <map>
#include <string>

class BaseModule
{
};

template<typename T> BaseModule* createT() { return new T; }

class BaseRegistry
{
    using map_type = std::map<std::string, BaseModule*(*)()>;
    static BaseModule* createInstance(std::string const& s) {
        map_type::iterator it = getMap()->find(s);
        if(it == getMap()->end())
            return nullptr;
        return it->second();
    }

protected:
    static map_type* getMap() {
        if(!map) { map = new map_type; }
        return map;
    }

private:
    static map_type* map;
};

template<typename T>
struct DerivedRegister : BaseRegistry {
    DerivedRegister(std::string const& s) {
        getMap()->insert(std::make_pair(s, &createT<T>));
    }
};

#endif // BASEMODULE_H

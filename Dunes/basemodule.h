#ifndef BASEMODULE_H
#define BASEMODULE_H
#include <map>
#include <string>
#include <QString>
#include <QPushButton>

class BaseModule : public QPushButton
{
};

template<typename T> BaseModule* createT() { return new T; }

class BaseRegistry
{
    using map_type = std::map<QString, BaseModule*(*)()>;
public:
    static BaseModule* createInstance(QString const& s) {
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
    DerivedRegister(QString const& s) {
        getMap()->insert(std::make_pair(s, &createT<T>));
    }
};

#endif // BASEMODULE_H

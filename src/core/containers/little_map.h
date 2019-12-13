#ifndef LITTLE_MAP_H
#define LITTLE_MAP_H

#include <initializer_list>
#include <utility>
#include <vector>

namespace core::containers
{

template<typename Key, typename Value>
class LittleMap
{
public:
    LittleMap() = default;
    LittleMap(const std::initializer_list<std::pair<Key, Value>>& l);

    Value& operator[](const Key& key);
    Value operator[](const Key& key) const;

    auto begin(){return data_.begin();}
    auto end(){return data_.end();}
private:
    std::vector<std::pair<Key, Value>> data_;
};

}

#include "little_map.hpp"

#endif //LITTLE_MAP_H

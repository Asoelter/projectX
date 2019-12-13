#include <algorithm>
#include <stdexcept>

namespace core::containers
{

template<typename Key, typename Value>
LittleMap<Key, Value>::LittleMap(const std::initializer_list<std::pair<Key, Value>>& l)
    : data_(l.begin(), l.end())
{
    
}

template<typename Key, typename Value>
Value& LittleMap<Key, Value>::operator[](const Key& key)
{
    using pairT = std::pair<Key, Value>;

    auto valueItr = std::find(data_.begin(), data_.end(), [&key](const pairT& p)
    {
        return p.first == key;
    });

    if(valueItr != data_.end())
    {
        return valueItr->second;
    }
    else
    {
        auto& newValue = data_.emplace_back(std::pair(key, Value()));

        return newValue.second;
    }
}

template<typename Key, typename Value>
Value LittleMap<Key, Value>::operator[](const Key& key) const
{
    using pairT = std::pair<Key, Value>;

    auto valueItr = std::find(data_.begin(), data_.end(), [&key](const pairT& p)
    {
        return p.first == key;
    });

    if(valueItr == data_.end())
    {
        throw std::invalid_argument("Key not found");
    }

    return valueItr->second;
}

}

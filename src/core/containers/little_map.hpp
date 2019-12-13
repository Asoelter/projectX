#include <algorithm>
#include <stdexcept>

namespace core::containers
{

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
        return *valueItr->second;
    }
    else
    {
        //TODO(asoelter): SFINAE out non-default-constructable classes 
        //and throw an exception if we get to this point
        const auto newValue = data_.emplace_back({key, Value()});
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

    return *valueItr->second;
}

}

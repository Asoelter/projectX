namespace core::containers
{

template<typename Key, typename Value>
LittleMap<Key, Value>::LittleMap()
    : data_()
{

}

template<typename Key, typename Value>
Value& LittleMap<Key, Value>::operator[](const Key& key)
{
    return Value();
}

template<typename Key, typename Value>
Value LittleMap<Key, Value>::operator[](const Key& key) const
{
    return Value();
}

}

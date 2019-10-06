#ifndef POINT_H
#define POINT_H

#include <type_traits>

namespace core::math
{
template
    <
    typename T, 
    typename = std::enable_if_t<std::is_arithmetic_v<T>>
    >
class Point
{
public:
    Point(T _x, T _y) 
        : x(_x)
        , y(_y)
        , z(T())
        , a(T())
        {

        }

    Point(T _x, T _y, T _z)
        : x(_x)
        , y(_y)
        , z(_z)
        , a(T())
        {

        }

    Point(T _x, T _y, T _z, T _a)
        : x(_x)
        , y(_y)
        , z(_z)
        {

        }


public:
    static constexpr auto size = 4;

    union
    {
        T values[size];
        struct
        {
            T x;
            T y;
            T z;
            T a;
        };
    };
};
}

#include "point.hpp"

#endif //POINT_H

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
    constexpr Point(T _x, T _y, T _z = T(), T _a = T()) noexcept
        : x(_x)
        , y(_y)
        , z(_z)
        , a(_a)
        {

        }

    constexpr Point& operator=(const Point& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        a = other.a;

        return *this;
    }

    bool operator==(const Point& rhs)
    {
        return x == rhs.x
            && y == rhs.y
            && z == rhs.z
            && a == rhs.a;
    }

    bool operator!=(const Point& rhs)
    {
        return !(this == rhs);
    }

    Point operator-(const Point&rhs)
    {
        return {x - rhs.x, y - rhs.y, z - rhs.z, a - rhs.a};
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
#endif //POINT_H

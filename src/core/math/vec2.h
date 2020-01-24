#ifndef VEC2_H
#define VEC2_H

#include <type_traits>

#include "math_traits.h"
#include "point.h"

namespace core::math
{
template<typename T, typename = EnableIfMath<T>>
class vec2
{
public:
    constexpr vec2(T _x, T _y)
        : x(_x)
        , y(_y)
    {

    }

    constexpr vec2(const vec2<T>& other) 
        : x(other.x)
        , y(other.y)
    {

    }

    [[nodiscard]]
    bool operator==(const vec2& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }

    [[nodiscard]]
    bool operator!=(const vec2& rhs)
    {
        return !(*this == rhs);
    }

    [[nodiscard]]
    constexpr vec2 operator+(const vec2& rhs)
    {
        return {x + rhs.x, y + rhs.y};
    }

    [[nodiscard]]
    constexpr vec2 operator-(const vec2& rhs) 
    {
        return {x - rhs.x, y - rhs.y};
    }

    [[nodiscard]]
    constexpr Point<T> operator+(const Point<T>& other)
    {
        return {other.x + x, other.y + y};
    }

    [[nodiscard]]
    friend constexpr Point<T> operator+(const Point<T>& other, const vec2& self)
    {
        return {other.x + self.x, other.y + self.y};
    }

    static constexpr size_t size = 2;

    union
    {
        T data[size];

        struct
        {
            T x;
            T y;
        };
    };
};


}

#endif //VEC2_H

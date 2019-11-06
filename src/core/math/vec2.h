#ifndef VEC2_H
#define VEC2_H

#include <type_traits>

#include "point.h"

template<typename T>
using EnableIfMath =  std::enable_if_t<std::is_arithmetic_v<T>>;

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

    friend constexpr vec2 operator+(const vec2& self, const vec2& rhs)
    {
        return {self.x + rhs.x, self.y + rhs.y};
    }

    friend constexpr vec2 operator-(const vec2& self, const vec2& rhs) 
    {
        return {self.x - rhs.x, self.y - rhs.y};
    }

    friend constexpr Point<T> operator+(const vec2& self, const Point<T>& other)
    {
        return {other.x + self.x, other.y + self.y};
    }

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

#include "vec2.hpp"

#endif //VEC2_H

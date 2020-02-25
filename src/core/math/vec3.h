#ifndef VEC3_H
#define VEC3_H

#include <type_traits>

#include "math_traits.h"
#include "point.h"
#include "vec2.h"

namespace core::math
{
template<typename T, typename = EnableIfMath<T>>
class vec3
{
public:
    constexpr vec3(T _x, T _y, T _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {

    }

    constexpr vec3(const vec3& other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
    {

    }

    constexpr explicit vec3(const vec2<T>& other, T _z = T(0))
        : x(other.x)
        , y(other.y)
        , z(_z)
    {

    }

    [[nodiscard]]
    bool operator==(const vec3& rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    [[nodiscard]]
    bool operator!=(const vec3& rhs)
    {
        return !(*this == rhs);
    }

    [[nodiscard]]
    constexpr vec3 operator+(const vec3& rhs) const
    {
        return {x + rhs.x, y + rhs.y, z + rhs.z};
    }

    constexpr vec3 operator+=(const vec3& rhs) 
    {
        *this = *this + rhs;
        return *this;
    }

    [[nodiscard]]
    constexpr vec3 operator-(const vec3& rhs)  const
    {
        return {x - rhs.x, y - rhs.y, z - rhs.z};
    }

    constexpr vec3 operator-=(const vec3& rhs) 
    {
        *this = *this - rhs;
        return *this;
    }

    [[nodiscard]]
    constexpr Point<T> operator+(const Point<T>& other)
    {
        return {other.x + x, other.y + y, other.z + z};
    }

    [[nodiscard]]
    friend constexpr Point<T> operator+(const Point<T>& other, const vec3& self)
    {
        return {other.x + self.x, other.y + self.y, other.z + self.z};
    }

    static constexpr size_t size = 3;

    union
    {
        T data[size];

        struct
        {
            T x;
            T y;
            T z;
        };
    };
};

}
#endif //VEC3_H

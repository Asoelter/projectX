#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "point.h"
#include "vec2.h"
#include "vec3.h"

namespace core::math
{

template<typename T> [[nodiscard]]
constexpr vec3<T> difference(const Point<T>& lhs, const Point<T>& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template<typename T> [[nodiscard]]
constexpr vec3<T> cross(const vec2<T>& lhs, const vec2<T>& rhs)
{
    const auto lhsz = T(0);
    const auto rhsz = T(0);

    const auto x = (lhs.y * rhsz) - (lhsz * rhs.y);
    const auto y = (lhsz * rhs.x) - (lhs.x * rhsz);
    const auto z = (lhs.x * rhs.y) - (lhs.y * rhs.x);

    return {x, y, z};
}

template<typename T> [[nodiscard]]
constexpr vec3<T> cross(const vec3<T>& lhs, const vec3<T>& rhs)
{
    const auto x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
    const auto y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
    const auto z = (lhs.x * rhs.y) - (lhs.y * rhs.x);

    return {x, y, z};
}

template<typename T, typename U, typename = EnableIfMath<T>> [[nodiscard]]
constexpr auto operator*(T lhs, const vec3<U>& rhs)
{
    return vec3<U>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

template<typename T> [[nodiscard]]
constexpr vec2<T> normalize(const vec2<T>& vec)
{
    const auto magnitude = static_cast<T>(sqrt(vec.x * vec.x + vec.y * vec.y));

    const auto x = vec.x / magnitude;
    const auto y = vec.y / magnitude;

    return {x, y};
}

template<typename T> [[nodiscard]]
constexpr vec3<T> normalize(const vec3<T>& vec)
{
    const auto magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

    const auto x = static_cast<T>(vec.x / magnitude);
    const auto y = static_cast<T>(vec.y / magnitude);
    const auto z = static_cast<T>(vec.z / magnitude);

    return {x, y, z};
}

}

#endif //OPERATIONS_H

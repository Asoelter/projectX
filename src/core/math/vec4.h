#ifndef VEC4_H
#define VEC4_H

template<typename T>
using EnableIfMath =  std::enable_if_t<std::is_arithmetic_v<T>>;

namespace core::math
{
template<typename T, typename = EnableIfMath<T>>
class vec4
{
public:
    constexpr vec4(T _x, T _y, T _z = 0, T _a = 0)
        : x(_x)
        , y(_y)
        , z(_z)
        , a(_a)
        {

        }

    constexpr T operator[](unsigned index) const
    {
        return data[index];
    }

    constexpr T& operator[](unsigned index) 
    {
        return data[index];
    }

    static constexpr size_t size = 4;

    static vec4 fromArray(const T data[size])
    {
        return vec4(data[0], data[1], data[2], data[3]);
    }

    union
    {
        T data[size];

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
#endif //VEC3_H

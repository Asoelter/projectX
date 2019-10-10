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
    vec4(T _x, T _y)
        : x(_x)
        , y(_y)
        , z(0)
        , a(0)
        {

        }
    vec4(T _x, T _y, T _z)
        : x(_x)
        , y(_y)
        , z(_z)
        , a(0)
        {

        }
    vec4(T _x, T _y, T _z, T _a)
        : x(_x)
        , y(_y)
        , z(_z)
        , a(_a)
        {

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

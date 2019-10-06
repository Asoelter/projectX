#ifndef VEC3_H
#define VEC3_H

template<typename T>
using EnableIfMath =  std::enable_if_t<std::is_arithmetic_v<T>>;

namespace core::math
{
template<typename T, typename = EnableIfMath<T>>
class vec3
{
public:
    vec3(T _x, T _y, T _z)
        : x(_x)
        , y(_y)
        , z(_z)
        {

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

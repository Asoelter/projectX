#ifndef VEC2_H
#define VEC2_H

template<typename T>
using EnableIfMath =  std::enable_if_t<std::is_arithmetic_v<T>>;

namespace core::math
{
template<typename T, typename = EnableIfMath<T>>
class vec2
{
public:
    vec2(T _x, T _y)
        : x(_x)
        , y(_y)
        {

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

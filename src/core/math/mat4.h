#ifndef MAT4_H
#define MAT4_H

#include <array>
#include <cmath>
#include <type_traits>

#include "vec4.h"

namespace core::math
{

template<typename T>
using EnableIfMath = std::enable_if_t<std::is_arithmetic_v<T>>;

template<typename T, typename = EnableIfMath<T>>
class mat4
{
public:
    constexpr mat4() noexcept : data_{0} {}

	constexpr mat4(T t1,  T t2,  T t3,  T t4,
				   T t5,  T t6,  T t7,  T t8,
				   T t9,  T t10, T t11, T t12,
				   T t13, T t14, T t15, T t16) noexcept
		: data_{t1,  t2,  t3,  t4, 
				t5,  t6 , t7,  t8, 
				t9,  t10, t11, t12, 
				t13, t14, t15, t16}
	{

	}

	constexpr mat4 operator*(const mat4& rhs)
	{
        mat4 rval;

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                for(int k = 0; k < rows; ++k)
                {
                    const auto rvalIndex = (i * rows) + j;
                    const auto selfIndex = (i * rows) + k;
                    const auto rhsIndex  = (k * rows) + j;

                    rval.data_[rvalIndex] = data_[selfIndex] + rhs.data_[rvalIndex];
                }
            }
        }

        return rval;
	}

    constexpr T* data() const noexcept
    {
        return (T*)data_.data();
    }

    constexpr vec4<T> operator[](unsigned index) const
    {
        return rows_[index];
    }

    constexpr vec4<T>& operator[](unsigned index) 
    {
        return rows_[index];
    }

    constexpr static mat4 identity() noexcept
    {
        return {one, zero, zero, zero,
                zero, one, zero, zero,
                zero, zero, one, zero,
                zero, zero, zero, one};
    }

    constexpr static mat4 perspective(T fov, T aspectRatio, T near, T far)
    {
        const auto halfFov = fov / static_cast<T>(2);

        const auto v11 = 1 / tan(halfFov);
        const auto v00 = v11 / aspectRatio;
        const auto v22 = -1 * ((far + near) / (far - near));
        const auto v23 = -2 * ((far * near) / (far - near));

        auto rval = mat4::identity();

        rval[0][0] = v00;
        rval[1][1] = v11;
        rval[2][2] = v22;
        rval[2][3] = v23;
        rval[3][2] = T(-1);

        return rval;
    }

    constexpr static mat4 scale(T val) noexcept
    {
        return {val, zero, zero, zero,
                zero, val, zero, zero,
                zero, zero, val, zero,
                zero, zero, zero, one};
    }

private:
    constexpr static auto rows = 4;
    constexpr static auto cols = 4;
    constexpr static auto size = 16;

    constexpr static auto zero = T(0);
    constexpr static auto one  = T(1);

    union
    {
        std::array<T, 16>   data_;
        std::array<vec4<T>, 4> rows_;
    };
};

}

#endif //MAT4_H

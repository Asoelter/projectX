#ifndef MAT4_H
#define MAT4_H

#include <array>
#include <cmath>
#include <iostream>
#include <type_traits>

#include "math_traits.h"
#include "operations.h"
#include "vec3.h"
#include "vec4.h"

namespace core::math
{

template<typename T, typename = EnableIfMath<T>>
class mat4
{
public:
    constexpr mat4() noexcept : elements_{0} {}

	constexpr mat4(T t1,  T t2,  T t3,  T t4,
				   T t5,  T t6,  T t7,  T t8,
				   T t9,  T t10, T t11, T t12,
				   T t13, T t14, T t15, T t16) noexcept
		: elements_{t1,  t2,  t3,  t4, 
				t5,  t6 , t7,  t8, 
				t9,  t10, t11, t12, 
				t13, t14, t15, t16}
	{

	}

    constexpr mat4(const mat4& rhs) noexcept
        : elements_(rhs.elements_)
    {
        
    }

    constexpr mat4& operator=(const mat4& rhs)
    {
        for(int i = 0; i < size; ++i)
        {
            elements_[i] = rhs.elements_[i];
        }

        return *this;
    }

	constexpr mat4 operator*(const mat4& rhs) const
	{
        mat4 rval;

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                auto sum = zero;

                for(int k = 0; k < rows; ++k)
                {
                    sum += (rows_[i][k] * rhs[k][j]);
                }

                rval[i][j] = sum;
            }
        }

        return rval;
	}

    constexpr const T* data() const noexcept
    {
        return elements_.data();
    }

    constexpr vec4<T> operator[](unsigned index) const
    {
        return rows_[index];
    }

    constexpr vec4<T>& operator[](unsigned index) 
    {
        return rows_[index];
    }

    static constexpr mat4 identity() noexcept
    {
        return {one, zero, zero, zero,
                zero, one, zero, zero,
                zero, zero, one, zero,
                zero, zero, zero, one};
    }

    static constexpr mat4 perspective(T fov, T aspectRatio, T near, T far)
    {
        const auto halfFov = fov / static_cast<T>(2);

        const auto v11 = 1 / tan(halfFov);
        const auto v00 = v11 / aspectRatio;
        const auto v22 = ((near + far) / (near - far));
        const auto v23 = 2 * ((near * far) / (near - far));

        auto rval = mat4::identity();

        rval[0][0] = v00;
        rval[1][1] = v11;
        rval[2][2] = v22;
        rval[2][3] = v23;
        rval[3][2] = T(-1);

        return rval;
    }

    static constexpr mat4 scale(T val) noexcept
    {
        return {val, zero, zero, zero,
                zero, val, zero, zero,
                zero, zero, val, zero,
                zero, zero, zero, one};
    }

    static constexpr mat4 translate(const vec3<T>& direction)
    {
        return {one, zero, zero, one,
                zero, one, zero, one,
                zero, zero, one, one,
                direction.x, direction.y, direction.z, one};
    }

    static constexpr auto lookAt(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up)
    {
        const auto forward = normalize(center - eye);
        const auto right = normalize(cross(normalize(up), forward));

        const auto rotation = mat4(right.x,     right.y,    right.z,    zero,
                                   up.x,        up.y,       up.z,       zero,
                                   forward.x,   forward.y,  forward.z,  zero,
                                   zero,        zero,       zero,       one);

        const auto translation = translate(-1 * eye);

        return rotation * translation;
    }

    static constexpr auto rows = 4;
    static constexpr auto cols = 4;
    static constexpr auto size = 16;

private:
    static constexpr auto zero = T(0);
    static constexpr auto one  = T(1);

    union
    {
        std::array<T, 16>       elements_;
        std::array<vec4<T>, 4>  rows_;
    };
};

template<typename T>
void print(const mat4<T>& mat)
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            std::cout << mat[i][j];
        }

        std::cout << '\n';
    }
}

}

#endif //MAT4_H

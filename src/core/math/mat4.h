#ifndef MAT4_H
#define MAT4_H

#include <array>
#include <type_traits>

namespace core::math
{

template<typename T>
using EnableIfMath = std::enable_if_v<std::is_arithmetic_v<T>>;

template<typename T, typename = EnableIfMathV<T>>
class mat4
{
public:
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

	}

private:
	std::array<T, 16> data_;
};

}

#endif //MAT4_H
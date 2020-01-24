#ifndef MATH_TRAITS_H
#define MATH_TRAITS_H

#include <type_traits>

template<typename T>
using EnableIfMath =  std::enable_if_t<std::is_arithmetic_v<T>>;

#endif //MATH_TRAITS_H

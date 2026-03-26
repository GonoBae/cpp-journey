#include <iostream>
#include <cstdint>

// 반환 타입 명시적 지정 가능
template <typename T, typename U>
auto max(T x, U y) -> std::common_type_t<T, U>
{
    return (x < y) ? y : x;
}
#include <iostream>
#include "add.hpp"

// 런타임 호출 원천 차단
// 이 함수는 반드시 컴파일 타임에만 호출
// 런타임 변수 넘기면 컴파일 에러
consteval int doSomething(int x, int y)
{
    x = x + 2;

    int z{x + y};
    if (x > y)
        z = z - 1;
    return z;
}

constexpr int doSomething2(int x, int y)
{
    x = x + 2;

    int z{x + y};
    if (x > y)
        z = z - 1;
    return z;
}

// 컴파일, 런타임 구분
#include <type_traits>

constexpr int someFunction()
{
    if (std::is_constant_evaluated())
    {
        // 컴파일 타임용 계산
        return 1;
    }
    else
    {
        // 런타임용 계산
        return 0;
    }
}

int const_exe()
{
    // const 보다 명확하게 컴파일 타임 확정임을 명시
    // const -> 런타임 초기화 가능
    // constexpr -> 컴파일 타임 값만 가능
    constexpr int g{doSomething(5, 6)};
    std::cout << g << '\n';

    // 런타임 변수가 파라미터로 들어가므로 에러 발생!
    // int x, y;
    // x = 1;
    // y = 2;
    // int a{doSomething(x, y)};
    // std::cout << a << '\n';

    // 런타임 변수 가능 (런타임으로 실행됨)
    // 상황에 따라 컴파일 또는 런타임으로 실행
    int x, y;
    x = 1;
    y = 2;
    int a{doSomething2(x, y)};
    std::cout << a << '\n';
    return 0;
}
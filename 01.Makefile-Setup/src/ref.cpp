#include <iostream>

int ref_exe()
{
    int x{1};
    int &ref{x};

    std::cout << x << ref << '\n';

    int y{2};
    // 참조 선언 시 바인딩이 고정되고 변경할 수 없음
    // 대상을 바꾸고 싶으면 포인터 사용
    ref = y;
    y = 3;
    std::cout << x << ref << '\n';

    x = 4;
    std::cout << x << ref << '\n';

    return 0;
}

int constref_exe()
{
    // 타입이 다른 const 참조에 바인딩 -> 임시 int 객체 만듦
    // bombs 가 0 이 되어도 you 는 1
    // 임시 객체는 수정이 불가능해야 하므로 const 여야 함
    short bombs{1};
    const int &you{bombs};
    --bombs;

    if (you)
    {
        std::cout << "Bombs away! Goodbye, cruel world.\n";
    }

    return 0;
}

// 값으로 전달되는 경우
// 1. 열거형
// 2. 뷰 및 범위 (std::string_view, std::span)
// 3. 참조 또는 (소유하지 않은)포인터를 모방하는 유형

// 왜 값으로 복사할까?
// 복사 비용은 바인딩 비용과 비슷하지만 객체에 접근하는 속도는 더 빠르고 컴파일러가 더 효율적으로 최적화 가능

// 참조에 의한 전달되는 경우
// 1. 함수에서 수정해야 하는 인수
// 2. 복사할 수 없는 유형 (std::ostream)
// 3. 복사로 인해 소유권 문제가 발생하여 이를 피하고자 하는 유형 (std::unique_ptr, std::shared_ptr)
// 4. 가상 함수를 가지고 있거나 상속될 가능성이 높은 유형
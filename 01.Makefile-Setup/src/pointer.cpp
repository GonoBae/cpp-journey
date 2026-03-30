#include <iostream>

int pointer_exe()
{
    // 상수 값을 가리키는 포인터를 선언하려면 데이터 형식 앞에 'const' 키워드 사용
    [[maybe_unused]] const int x{5};
    [[maybe_unused]] const int *ptr{&x};

    // const 포인터 - 재할당 불가
    [[maybe_unused]] int y{6};
    [[maybe_unused]] int *const ptry{&y};

    // 상수를 가리키는 const 포인터
    [[maybe_unused]] const int *const constptr{&x};

    // std::cout << ptr << '\n'
    //           << ptry << '\n'
    //           << constptr << '\n';

    return 0;
}

constexpr std::string_view hello{"Hello"};
constexpr const std::string_view &getConstRef()
{
    return hello;
}

int ref_level_exe()
{
    // top-level : x 자체가 const
    // low-level : 가리키는 대상이 const

    [[maybe_unused]] auto ref1{getConstRef()};                  // & 가 아니라 복사, top-level const 제거
    [[maybe_unused]] constexpr auto ref2{getConstRef()};        // & 가 아니라 복사, top-level const 제거
    [[maybe_unused]] auto &ref3{getConstRef()};                 // & 가 있어서 참조, low-level const 유지
    [[maybe_unused]] constexpr const auto &ref4{getConstRef()}; // & 가 있어서 참조, low-level const 유지
    return 0;
}

int auto_exe()
{
    std::string s{};
    const std::string *const ptr{&s};

    // 타입 추론
    // 최상위 const 제거 (const std::string* [const])
    // constexpr - 추론되지 않음. 명시적 적용 필요
    // 포인터를 삭제하지 않음

    // const std::string* 까지 추론
    [[maybe_unused]] auto ptr1{ptr};
    [[maybe_unused]] auto *ptr2{ptr};

    // auto const , const auto - 포인터를 상수 포인터로 만듦
    [[maybe_unused]] auto const ptr3{ptr};
    [[maybe_unused]] const auto ptr4{ptr};

    // auto* const , const auto* - 포인터를 const 포인터로 만듦
    // * 앞까지 추론
    [[maybe_unused]] auto *const ptr5{ptr};
    // const std::string 으로 추론
    // const 가 이미 있기에 const std::string 추론 그대로 사용
    [[maybe_unused]] const auto *ptr6{ptr};

    // 컴파일러는 * 이 없으면 구분하지 못함. const 가 중복으로 나왔다고 판단
    // [[maybe_unused]] const auto const ptr7{ptr};
    [[maybe_unused]] const auto *const ptr8{ptr};
    return 0;
}

// 최상위 상수 - const int x / int* const ptr -> 객체 자체에 적용
// 저수준 상수 - const int& ref / const int* ptr -> 참조 또는 포인터를 통해 접근하는 객체에 적용

#include <optional>

void printIDNumber(const int *id = nullptr)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

void printIDNumberOptional(std::optional<const int> id = std::nullopt)
{
    if (id)
        std::cout << "Your ID number is " << id.value() << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int optional_exe()
{
    printIDNumberOptional();
    int userid{34};
    printIDNumberOptional(userid);
    return 0;
}
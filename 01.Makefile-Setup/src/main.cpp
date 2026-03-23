#include <iostream>
#include <vector>
#include <string>
#include <ranges>   // C++20 ranges
#include <format>   // C++20 format
#include <concepts> // C++20 concepts

// ── C++20 Concept ────────────────────────────────────────────────────────────
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Concept 을 사용한 함수 템플릿
template <Numeric T>
T add(T a, T b)
{
    return a + b;
}

// ── C++20 Designated Initializers ────────────────────────────────────────────
struct Point
{
    int x;
    int y;
    std::string label;
};

int main()
{
    // C++20 std::format
    std::cout << std::format("=== C++20 Feature Demo ===\n\n");

    // Designated initializers
    Point p = {.x = 10, .y = 20, .label = "origin"};
    std::cout << std::format("Point: ({}, {}) label={}\n", p.x, p.y, p.label);

    // C++20 ranges::views::iota + filter + transform
    auto even_squares = std::views::iota(1, 11) | std::views::filter([](int n)
                                                                     { return n % 2 == 0; }) |
                        std::views::transform([](int n)
                                              { return n * n; });

    std::cout << "\n짝수의 제곱 (1~10): ";
    for (int v : even_squares)
        std::cout << std::format("{} ", v);
    std::cout << "\n";

    // Concept 사용
    std::cout << std::format("\nadd<int>(3, 4)    = {}\n", add(3, 4));
    std::cout << std::format("add<double>(1.5, 2.5) = {}\n", add(1.5, 2.5));

    // C++20 range-based for with initializer
    std::vector<std::string> langs = {"C++20", "Makefile", "Cross-Platform"};
    for (int i = 0; auto &lang : langs)
        std::cout << std::format("  [{}] {}\n", i++, lang);

    return 0;
}

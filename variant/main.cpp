#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

template <class T>
struct always_false : std::false_type
{
};

template <class... Ts>
struct overloaded : Ts...
{
    overloaded(Ts... ts) : Ts(ts)...
    {
    }
    using Ts::operator()...;
};

using var = std::variant<int, long, double, std::string>;

template <typename... Ts>
void print(Ts&&... var)
{
    (std::visit(
         [](auto&& arg) {
             using T = std::decay_t<decltype(arg)>;
             if
                 constexpr(std::is_same_v<T, int>)
                 {
                     std::cout << "int " << arg << '\n';
                 }
             else if
                 constexpr(std::is_same_v<T, double>)
                 {
                     std::cout << "double " << arg << '\n';
                 }
             else
             {
                 static_assert(always_false<T>::value,
                               "non-exhaustive visitor!");
             }
         },
         std::forward<Ts>(var)),
     ...);
}

int main()
{
    std::vector<var> vec = {1, 15l, 1.5, "hi"};
    overloaded ov{[](auto arg) { std::cout << "other " << arg << '\n'; },
                  [](long arg) { std::cout << "long " << arg << '\n'; },
                  [](double arg) { std::cout << "double " << arg << '\n'; },
                  [](std::string arg) { std::cout << "string " << arg << '\n'; }};
    for (auto& v : vec)
    {
        std::visit(ov, v);
    }
    print(std::variant<int, double>{1}, std::variant<int, double>{2.0});
}

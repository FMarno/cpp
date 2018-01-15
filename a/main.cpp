#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

class What {
public:
    int a;
    bool b = true;

    What() : 
        a(5),
        b(false)
    {
    }
};
template <typename... Ns, typename = std::enable_if_t<(std::is_arithmetic<Ns>::value && ...)>>
auto sum(Ns... x) {
    return (x + ... + 0);
}

template <typename... Ts>
void print(Ts&&... ts)
{
    ((std::cout << std::forward<Ts>(ts) << '\n'), ...);
}

void inc(int* const i)
{
    (*i)++;
}
int main()
{
    int a(5);
    std::cout << a << '\n';
    int* ptr = &a;
    inc(ptr);
    std::cout << a << '\n';
}

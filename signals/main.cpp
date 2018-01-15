#include <boost/signals2.hpp>
#include <iostream>
struct HelloWorld
{
    void operator()() const
    {
        std::cout << "Hello, World!" << std::endl;
    }
};
struct Hello
{
    void operator()() const
    {
        std::cout << "Hello";
    }
};
struct World
{
    void operator()() const
    {
        std::cout << ", World!" << std::endl;
    }
};

int main()
{
    boost::signals2::signal<void()> sig;
    // connect a HelloWorld slot
    Hello hello;
    World world;
    sig.connect(0, world);
    sig.connect(hello);
    sig();
}

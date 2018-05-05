#include <iostream>

class A {
    public:
        virtual void Hello()
        {
            std::cout << "hello A\n";
        }   
};
class B {
    public:
        virtual void Hello()
        {
            std::cout << "hello B\n";
        }   
};
class C: public A, public B {
public:
    void Hello() override
    {
        std::cout << "hello C\n";
    }
};

int main(){
    C c;
    c.Hello();
};

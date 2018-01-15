#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

int main(){
    std::thread t([] {
        std::ofstream testFile{"test.txt", std::ofstream::out};
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        for (char i = 'a'; i < 'z' + 1; i++)
        {
            testFile << i;
            testFile.flush();
        }
    });
    std::thread t2([] {
        std::ofstream testFile{"test.txt", std::ofstream::out};
        for (char i = 'A'; i < 'Z' + 1; i++)
        {
            testFile << i;
            testFile.flush();
        }
    });
    t.join();
    t2.join();
}

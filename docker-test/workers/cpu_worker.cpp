#include <chrono>
#include <thread>
#include <iostream>
#include <ctime>

int main()
{
    while(true){
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::cout << std::time(nullptr) << std::endl;
    }
}
#include <chrono>
#include <thread>
#include <iostream>
#include <ctime>
#include <vector>

int main()
{
    auto data = std::vector<int>();
    data.resize(500'000'000);

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << std::time(nullptr) << " " << data.size() << std::endl;
    }
}
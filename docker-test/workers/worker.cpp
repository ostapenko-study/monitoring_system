#include <chrono>
#include <thread>
#include <iostream>
#include <ctime>
#include <vector>

int main()
{
    auto data = std::vector<int>();
    data.resize(250'000'000);

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        long sum = 0;
        for(auto x : data)
        {
            sum += x;
        }
        std::cout << std::time(nullptr) << " " << sum << std::endl;
    }
}
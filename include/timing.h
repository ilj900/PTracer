#pragma once

#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer() {StartTime = std::chrono::steady_clock::now();};
    ~Timer() {std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - StartTime).count() <<std::endl;};
private:
    std::chrono::time_point<std::chrono::steady_clock> StartTime;
};
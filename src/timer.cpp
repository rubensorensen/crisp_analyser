#include "timer.hpp"

Timer& Timer::Get()
{
    static Timer instance;
    return instance;
}

void Timer::Init()
{
    Get().m_Time = std::chrono::high_resolution_clock::now();
}

double Timer::DeltaTime()
{
    auto previous = Get().m_Time;
    Get().m_Time  = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(Get().m_Time - previous).count();
}
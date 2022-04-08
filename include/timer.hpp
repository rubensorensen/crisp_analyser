#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer
{
  public:

    static void Init();
    static double DeltaTime();

  private:

    Timer()             = default;
    Timer(const Timer&) = delete;
    ~Timer()            = default;
    static Timer& Get();

  private:

    std::chrono::time_point<std::chrono::high_resolution_clock> m_Time;
};

#endif  // TIMER_HPP
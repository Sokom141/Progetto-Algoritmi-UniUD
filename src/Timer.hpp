#ifndef _TIMER_C_H
#define _TIMER_C_H

#include <vector>
#include <chrono>

/**
 * @brief An easy to use timer based on RAII to reduce boilerplate code. 
 * When the destructor is called the timer is stopped and the result is 
 * pushed on the specified vector.
 * @param <T> the type of vector
 * @param <U> the std::chrono type
 */
template <class T, class U>
class Timer
{
private:
    std::vector<T> &m_v;
    std::chrono::_V2::steady_clock::time_point m_start;
    std::chrono::_V2::steady_clock::time_point m_end;

public:
    Timer(std::vector<T> &v_ref) : m_v{v_ref}, m_start{std::chrono::steady_clock::now()}
    {
    }

    ~Timer()
    {
        m_end = std::chrono::steady_clock::now();
        m_v.push_back(std::chrono::duration_cast<U>(m_end - m_start).count());
    }
};

#endif // _TIMER_C_H
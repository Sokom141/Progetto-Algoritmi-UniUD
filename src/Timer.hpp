#ifndef _TIMER_C_H
#define _TIMER_C_H

#include <vector>
#include <chrono>

/**
 * An easy to use timer based on RAII to reduce boilerplate code. 
 * When the destructor is called the timer is stopped and the result is 
 * pushed on the specified vector.
 * @param <T> the type of vector
 * @param <U> the std::chrono type
 */
template <class T, class U>
class Timer
{
private:
    std::vector<T> &v;
    std::chrono::_V2::steady_clock::time_point start;
    std::chrono::_V2::steady_clock::time_point end;

public:
    Timer(std::vector<T> &v_ref) : v{v_ref}
    {
        start = std::chrono::steady_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::steady_clock::now();
        v.push_back(std::chrono::duration_cast<U>(end - start).count());
    }
};

#endif // _TIMER_C_H
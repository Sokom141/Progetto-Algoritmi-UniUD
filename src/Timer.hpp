#ifndef _TIMER_C_H
#define _TIMER_C_H

#include <vector>
#include <chrono>

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
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "core.hpp"

std::string generate_random_str(const int length, const int char_num)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long ms{tp.tv_sec * 1000 + tp.tv_usec / 1000};
    std::srand(ms);

    std::string str(length, 'a');
    int rand_period = (std::rand() % length) + 1;

    for (int i = 0; i < rand_period; ++i)
    {
        str[i] = (std::rand() % char_num) + 'a';
    }

    for (int i = 0; i < length; ++i)
    {
        str[i] = str[i % rand_period];
    }

    return str;
}

int period_naive(const std::string &str)
{
    const int n = str.length();

    for (int i = 1; i <= n; ++i)
    {
        std::string str1 = str.substr(0, n - i);
        std::string str2 = str.substr(i, n - i);

        if (str1.compare(str2) == 0)
        {
            return i;
        }
    }

    return n;
}

int period_smart(const std::string &str)
{
    const int n = str.length();

    std::vector<int> vec;
    vec.reserve(n);
    vec.push_back(0);

    for (int i = 1; i < n; ++i)
    {
        int z = vec[i - 1];

        while (z > 0 && str[z] != str[i])
        {
            z = vec[z - 1];
        }

        if (str[z] == str[i])
        {
            vec.push_back(z + 1);
        }
        else
        {
            vec.push_back(0);
        }
    }

    return n - vec[n - 1];
}

double get_system_resolution()
{
    auto start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end;

    do
    {
        end = std::chrono::steady_clock::now();
    } while (start == end);

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

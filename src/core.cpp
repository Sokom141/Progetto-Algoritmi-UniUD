#include <iostream>
#include <sys/time.h>
#include "core.hpp"

std::string generate_random_str(const int length, const int char_num)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
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
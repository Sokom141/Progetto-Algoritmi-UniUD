#include <iostream>
#include <vector>
#include <chrono>
#include <string.h>
#include <cmath>
#include <array>
#include "core.hpp"
#include "Timer.hpp"

void debug_main();
void calc_time();

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (strncmp(argv[1], "--debug", 8) == 0)
        {
            debug_main();
            return EXIT_SUCCESS;
        }
    }

    calc_time();

    return EXIT_SUCCESS;
}

void calc_time()
{
    constexpr int a{1000};
    constexpr int b{500000};
    const auto c{exp(((log(b)) - log(a)) / 119)};

    constexpr int iter{120};
    constexpr int precision{200};
    using t_precision = std::chrono::nanoseconds;

    constexpr double max_error{0.001};
    const auto resolution{get_system_resolution()};

    const int t_min{resolution * ((1 / max_error) + 1)};

    bool naive_run = true;
    std::vector<double> avg_smart_t;
    std::vector<double> avg_naive_t;
    avg_smart_t.reserve(iter);
    avg_naive_t.reserve(iter);

    std::vector<std::pair<int, double>> smart_t;
    std::vector<std::pair<int, double>> naive_t;
    smart_t.reserve(iter);
    naive_t.reserve(iter);

    std::array<std::string, precision> strs;

    for (int i = 0; i < iter; ++i)
    {
        int n{a * pow(c, i)};
        int count{0};

        for (int j = 0; j < precision; ++j)
        {
            strs[j] = generate_random_str(n, 2);
        }

        // Period smart timing:

        {
            Timer<double, t_precision> tmr(avg_smart_t);

            do
            {
                period_smart(strs[count]);
                ++count;
            } while (tmr.get_current_time() <= t_min);
        }

        avg_smart_t[i] /= count;
        smart_t.push_back({n, avg_smart_t[i]});

        // reset counter
        count = 0;

        // Period naive timing:

        if (i > 0 && avg_naive_t[i - 1] > 2200000000.0) // nanoseconds
        {
            naive_run = false;
        }

        if (naive_run)
        {
            {
                Timer<double, t_precision> tmr(avg_naive_t);

                do
                {
                    period_naive(strs[count]);
                    ++count;
                } while (tmr.get_current_time() <= t_min);
            }
            avg_naive_t[i] /= count;
            naive_t.push_back({n, avg_naive_t[i]});
        }

        std::cout << i << '/' << iter << '\n';
    }

    write_csv("tempi_smart.csv", smart_t, "N", "TIME");
    write_csv("tempi_naive.csv", naive_t, "N", "TIME");
}

void debug_main()
{
    std::vector<std::pair<int, double>> v{{1, 0.53}, {5, 9.99}, {10, 14.002}, {100, 140.002}, {1000, 1400.002}};
    std::vector<double> v1{};

    auto s = generate_random_str(5000, 10);

    std::cout << s << '\n';

    auto time = get_system_resolution();

    std::cout << time << "ns\n";

    int a, b;
    {
        Timer<double, std::chrono::nanoseconds> t{v1};
        a = period_naive(s);
    }

    {
        Timer<double, std::chrono::nanoseconds> t{v1};
        b = period_smart(s);
    }

    std::cout << "Naive implementation result: " << a << " time: " << v1[0] << "ns\n";
    std::cout << "Smart implementation result: " << b << " time: " << v1[1] << "ns\n";

    for (const auto &i : v1)
    {
        std::cout << i << "ns\n";
    }

    write_csv("tempi.csv", v, "N", "TIME");
}
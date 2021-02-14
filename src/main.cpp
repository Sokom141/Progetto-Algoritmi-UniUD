#include <iostream>
#include <vector>
#include <chrono>
#include <string.h>
#include <cmath>
#include <array>
#include "core.hpp"
#include "Timer.hpp"

void calc_time(random_str_method str_method);
void calc_distribution();
void calc_var(random_str_method str_method);

constexpr int a{1000};
constexpr int b{500000};
const auto c{exp(((log(b)) - log(a)) / 119)};
constexpr int iter{120};
constexpr int precision{200};
using t_precision = std::chrono::nanoseconds;
constexpr double max_error{0.001};
const auto resolution{get_system_resolution()};
const int t_min{resolution * ((1 / max_error) + 1)};

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (strncmp(argv[1], "--debug", 7) == 0)
        {
            auto s = generate_random_str(500000, 2, random_str_method::ONE);
            std::cout << period_smart(s) << '\n';

            s = generate_random_str(500000, 2, random_str_method::TWO);
            std::cout << period_smart(s) << '\n';

            s = generate_random_str(500000, 2, random_str_method::THREE);
            std::cout << period_smart(s) << '\n';

            s = generate_random_str(500000, 2, random_str_method::FOUR);
            std::cout << period_smart(s) << '\n';

            return EXIT_SUCCESS;
        }

        if (strncmp(argv[1], "--one", 5) == 0)
        {
            calc_time(random_str_method::ONE);
        }
        else if (strncmp(argv[1], "--two", 5) == 0)
        {
            calc_time(random_str_method::TWO);
        }
        else if (strncmp(argv[1], "--three", 7) == 0)
        {
            calc_time(random_str_method::THREE);
        }
        else if (strncmp(argv[1], "--four", 6) == 0)
        {
            calc_time(random_str_method::FOUR);
        }
        else if (strncmp(argv[1], "--distribution", 14) == 0)
        {
            calc_distribution();
        }
        else if (strncmp(argv[1], "--var", 5) == 0)
        {
            calc_var(random_str_method::TWO);
        }
    }

    return EXIT_SUCCESS;
}

void calc_time(random_str_method str_method)
{
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

        // String generation:

        for (int j = 0; j < precision; ++j)
        {
            strs[j] = generate_random_str(n, 2, str_method);
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

        std::cout << i + 1 << '/' << iter << '\n';
    }

    write_csv("tempi_smart_" + name(str_method) + ".csv", smart_t, "N", "TIME");
    write_csv("tempi_naive_" + name(str_method) + ".csv", naive_t, "N", "TIME");
}

void calc_distribution()
{
    std::array<std::string, precision> strs;
    std::vector<std::pair<int, int>> periods;
    for (int i = 0; i < precision; ++i)
    {
        strs[i] = generate_random_str(100, 2, random_str_method::ONE);
        periods.push_back({100, period_smart(strs[i])});
    }
    write_csv("distrib_one.csv", periods, "N", "PERIOD");
    periods.clear();

    for (int i = 0; i < precision; ++i)
    {
        strs[i] = generate_random_str(100, 2, random_str_method::TWO);
        periods.push_back({100, period_smart(strs[i])});
    }
    write_csv("distrib_two.csv", periods, "N", "PERIOD");
    periods.clear();

    for (int i = 0; i < precision; ++i)
    {
        strs[i] = generate_random_str(100, 2, random_str_method::THREE);
        periods.push_back({100, period_smart(strs[i])});
    }
    write_csv("distrib_three.csv", periods, "N", "PERIOD");
    periods.clear();

    for (int i = 0; i < precision; ++i)
    {
        strs[i] = generate_random_str(100, 2, random_str_method::FOUR);
        periods.push_back({100, period_smart(strs[i])});
    }
    write_csv("distrib_four.csv", periods, "N", "PERIOD");
}

void calc_var(random_str_method str_method)
{
    bool naive_run = true;

    std::vector<std::pair<int, double>> smart_t;
    std::vector<std::pair<int, double>> naive_t;
    smart_t.reserve(iter);
    naive_t.reserve(iter);

    std::vector<double> v_smart_t;
    std::vector<double> v_naive_t;
    v_smart_t.reserve(iter * 10);
    v_naive_t.reserve(iter * 10);

    std::array<std::string, precision> strs;

    for (int i = 0; i < iter; ++i)
    {
        int n{a * pow(c, i)};
        int count{0};

        // String generation:

        for (int j = 0; j < precision; ++j)
        {
            strs[j] = generate_random_str(n, 2, str_method);
        }

        // Period smart var timing:

        {
            do
            {
                {
                    Timer<double, t_precision> tmr(v_smart_t);
                    period_smart(strs[count]);
                }
                ++count;
            } while (count < 20);
        }

        for (int i = 0; i < count; ++i)
        {
            smart_t.push_back({n, v_smart_t[i]});
        }
        // reset counter
        count = 0;

        // Period naive var timing:

        if (i > 0 && naive_t[naive_t.size() - 1].second > 2200000000.0) // nanoseconds
        {
            naive_run = false;
        }

        if (naive_run)
        {
            {
                do
                {
                    {
                        Timer<double, t_precision> tmr(v_naive_t);
                        period_naive(strs[count]);
                    }
                    ++count;
                } while (count < 20);
            }

            for (int i = 0; i < count; ++i)
            {
                naive_t.push_back({n, v_naive_t[i]});
            }
        }

        std::cout << i + 1 << '/' << iter << '\n';

        v_naive_t.clear();
        v_smart_t.clear();
    }

    write_csv("var_smart.csv", smart_t, "N", "TIME");
    write_csv("var_naive.csv", naive_t, "N", "TIME");
}

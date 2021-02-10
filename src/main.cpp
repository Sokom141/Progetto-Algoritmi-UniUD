#include <iostream>
#include <vector>
#include <chrono>
#include "core.hpp"
#include "Timer.hpp"

int main(int argc, char **argv)
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

    return EXIT_SUCCESS;
}
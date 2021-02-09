#include <iostream>
#include <vector>
#include "core.hpp"

int main(int argc, char **argv)
{
    auto s = generate_random_str(50, 10);

    std::cout << s << '\n';

    auto time = get_system_resolution();

    std::cout << time << "ns\n";

    auto a = period_naive(s);
    auto b = period_smart(s);

    std::cout << "Naive implementation result: " << a << "\nSmart implementation result: " << b << '\n';

    std::vector<std::pair<int, double>> v{{1, 1.00}, {5, 9.99}, {10, 10.00}};

    write_csv("test.csv", v, "N", "TIME");

    return EXIT_SUCCESS;
}
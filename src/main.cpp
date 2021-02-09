#include <iostream>
#include "core.hpp"

int main(int argc, char **argv)
{
    auto s = generate_random_str(100, 10);

    std::cout << s << '\n';

    return EXIT_SUCCESS;
}
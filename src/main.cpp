#include <iostream>
#include "core.hpp"

int main(int argc, char **argv)
{
    //std::srand((unsigned)time(NULL));

    auto s = generate_random_str(100, 10);

    std::cout << s << '\n';

    return EXIT_SUCCESS;
}
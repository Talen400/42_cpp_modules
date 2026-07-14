#include "RPN.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    int result = RPN::evaluate(argv[1]);
    if (result == -1)
        return 1;

    std::cout << result << std::endl;
    return 0;
}

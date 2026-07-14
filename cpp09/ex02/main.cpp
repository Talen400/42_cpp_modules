#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::vector<int> input;
    for (int i = 1; i < argc; i++) {
        char* end;
        long n = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || n < 0) {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        input.push_back(static_cast<int>(n));
    }

    PmergeMe::sortAndMeasure(input);
    return 0;
}

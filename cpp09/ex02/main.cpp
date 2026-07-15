#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int> input;
	for (int i = 1; i < argc; i++) {
		int n;
		std::istringstream iss(argv[i]);
		if (!(iss >> n) || n < 0) {
			std::cerr << "Error" << std::endl;
			return 1;
		}
		input.push_back(n);
	}

	PmergeMe::sortAndMeasure(input);
	return 0;
}

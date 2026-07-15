#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange exchange;
	if (!exchange.loadDatabase("data.csv")) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::string header;
	std::getline(input, header);

	std::string line;
	while (std::getline(input, line)) {
		exchange.processLine(line);
	}

	return 0;
}

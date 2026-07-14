#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());

    if (m < 1 || m > 12 || d < 1 || d > 31)
        return false;

    if (m == 2 && d > 29)
        return false;
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
        return false;

    return true;
}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        return false;

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        size_t comma = line.find(',');
        if (comma == std::string::npos)
            continue;

        std::string date = line.substr(0, comma);
        double rate = std::strtod(line.substr(comma + 1).c_str(), NULL);

        _rates[date] = rate;
    }

    return true;
}

double BitcoinExchange::getRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = _rates.find(date);
    if (it != _rates.end())
        return it->second;

    it = _rates.lower_bound(date);
    if (it != _rates.begin())
        --it;
    else
        return -1;

    return it->second;
}

double BitcoinExchange::processLine(const std::string& line) const {
    if (line.empty())
        return -2;

    std::istringstream iss(line);
    std::string date, sep;
    double value;

    if (!(iss >> date >> sep >> value) || sep != "|") {
        std::cout << "Error: bad input => " << line << std::endl;
        return -2;
    }

    if (!isValidDate(date)) {
        std::cout << "Error: bad input => " << date << std::endl;
        return -2;
    }

    if (value < 0) {
        std::cout << "Error: not a positive number." << std::endl;
        return -2;
    }

    if (value > 1000) {
        std::cout << "Error: too large a number." << std::endl;
        return -2;
    }

    double rate = getRate(date);
    if (rate < 0) {
        std::cout << "Error: no exchange rate available for " << date << std::endl;
        return -2;
    }

    double result = value * rate;
    std::cout << date << " => " << value << " = " << result << std::endl;
    return result;
}

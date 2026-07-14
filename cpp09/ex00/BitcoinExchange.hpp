#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _rates;

    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    bool isValidDate(const std::string& date) const;

public:
    BitcoinExchange();
    ~BitcoinExchange();

    bool loadDatabase(const std::string& filename);
    double getRate(const std::string& date) const;
    double processLine(const std::string& line) const;
};

#endif

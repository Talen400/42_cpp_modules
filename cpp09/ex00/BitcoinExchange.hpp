#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
	private:
    	std::map<std::string, float> _rates;

		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		
		bool isValidDate(const std::string& date) const;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		
		bool loadDatabase(const std::string& filename);
		float getRate(const std::string& date) const;
		float processLine(const std::string& line) const;
};

#endif

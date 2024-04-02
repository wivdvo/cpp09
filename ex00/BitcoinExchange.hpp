#pragma once

#include <map>
#include <string>

class BitcoinExchange
{
	public:

		static void doExchange(char* fileString);

	private:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		static void splitLine(std::string line);
		static void checkDate(std::string date);

		static std::map<size_t, float> _db;
};

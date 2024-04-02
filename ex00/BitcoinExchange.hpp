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
		static int getCurrentYear(void);
		static void checkValue(float value);
		static void checkValue(int value);
		static void checkValueString(std::string value);

		static std::map<size_t, float> _db;
};

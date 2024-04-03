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

		static void splitLineData(std::string line);
		static void checkDate(std::string date);
		static int getCurrentYear(void);
		static void checkValue(float value);
		static void checkValue(int value);
		static void checkValueString(std::string value);
		static void handleData(void);
		static void handleInputAndConvert(char* fileString);
		static void splitLineInput(std::string line);
		static float getRate(size_t date);

		static std::map<size_t, float> _db;
};

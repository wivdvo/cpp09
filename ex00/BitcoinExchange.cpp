#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	this->_db = other._db;

	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::map<size_t, float> BitcoinExchange::_db;

void BitcoinExchange::doExchange(char* fileString)
{
	(void)fileString;

	std::ifstream data("data.csv");
	if (!data)
		throw std::runtime_error("Could not open file");
	

	std::string line;
	int i = 0;
	while (std::getline(data, line))
	{
		if (i++ != 0)
			splitLine(line);
	}
}

void BitcoinExchange::splitLine(std::string line)
{
	std::istringstream ss(line);
	std::string dateString;
	std::string valueString;

	//seperate line into to parts seperatored by ','
	std::getline(ss, dateString, ',');
	std::getline(ss, valueString);

	//std::cout << dateString << std::endl;

	checkDate(dateString);

	//convert value string to float
	float value;
	std::istringstream(valueString) >> value;

	//remove '-' and convert date to int 
	dateString.erase(std::remove(dateString.begin(), dateString.end(), '-'), dateString.end());
	size_t date;
	std::istringstream(dateString) >> date;

	//std::cout << "date " << date << "----" << "value " << value << std::endl;
	
	_db[date] = value;
}

void BitcoinExchange::checkDate(std::string date)
{
	//basic format checks
	if (date.size() != 10)
		throw std::runtime_error("Date is invalid. (lenght)");

	if (date[4] != '-' || date[7] != '-')
		throw std::runtime_error("Date is invalid. (missplaced '-')");

	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (std::isdigit(date[i]) == 0)
			throw std::runtime_error("Date is invalid. (non digit)");
	}

	//sperate values
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

	//check year
	if (year < 2009)
		throw std::runtime_error("Date is before BTC release.");
	if (year > getCurrentYear())
		throw std::runtime_error("Date is in future.");

	//check month and day
	if (month < 1 || month > 12)
		throw std::runtime_error("Date is invalid.");
    if (day < 1 || day > 31)
		throw std::runtime_error("Date is invalid.");
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		throw std::runtime_error("Date is invalid.");
    if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (!isLeapYear && day > 28))
			throw std::runtime_error("Date is invalid.");
    }
}



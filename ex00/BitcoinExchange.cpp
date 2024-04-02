#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

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

	std::cout << dateString << std::endl;

	checkDate(dateString);

	//convert value string to float
	float value;
	std::istringstream(valueString) >> value;

	//remove '-' and convert date to int 
	dateString.erase(std::remove(dateString.begin(), dateString.end(), '-'), dateString.end());
	size_t date;
	std::istringstream(dateString) >> date;

	std::cout << "date " << date << "----" << "value " << value << std::endl;
	
	_db[date] = value;
}

void BitcoinExchange::checkDate(std::string date)
{
	if (date.size() != 10)
		throw std::runtime_error("Date is invalid. (size)");
	if (date[4] != '-' || date[7] != '-')
		throw std::runtime_error("Date is invalid. '-'");
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (std::isdigit(date[i]) == 0)
			throw std::runtime_error("Date is invalid. (non alpha)");
	}
	

	std::cout << "date true" << std::endl;
}

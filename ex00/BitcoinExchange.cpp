#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <limits>

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

	checkAndReadData();
	checkAndReadInput(fileString);
}

void BitcoinExchange::checkAndReadInput(char* filestring)
{
	std::ifstream input(filestring);
	if (!input)
		throw std::runtime_error("Could not open file.");

	std::string line;
	int i = 0;
	while (std::getline(input, line))
	{
		if (i++ != 0)
			splitLineInput(line);
	}
}

void BitcoinExchange::splitLineInput(std::string line)
{
	//remove all spaces in line
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	
	//seperate line into to parts seperatored by '|'
	std::istringstream ss(line);
	std::string dateString;
	std::string valueString;
	std::getline(ss, dateString, '|');
	std::getline(ss, valueString);

	try {
		checkDate(dateString);
	} catch (std::exception& e){
		std::cerr << e.what() << std::endl;
	}

	try {
		checkValueString(valueString);
	} catch (std::exception& e){
		std::cerr << e.what() << std::endl;
	}

	//convert value string to float
	float value;
	std::istringstream(valueString) >> value;

	//check for overflow by comparing to infinity
	try {
		if (value == std::numeric_limits<float>::infinity() || value == -std::numeric_limits<float>::infinity())
			throw std::runtime_error("Value overflowed.");
		checkValue(value);
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void BitcoinExchange::checkAndReadData()
{
	std::ifstream data("data.csv");
	if (!data)
		throw std::runtime_error("Could not open file.");
	

	std::string line;
	int i = 0;
	while (std::getline(data, line))
	{
		if (i++ != 0)
			splitLineData(line);
	}
}

void BitcoinExchange::splitLineData(std::string line)
{
	std::istringstream ss(line);
	std::string dateString;
	std::string valueString;

	//seperate line into to parts seperatored by ','
	std::getline(ss, dateString, ',');
	std::getline(ss, valueString);

	//std::cout << dateString << std::endl;
	
	checkDate(dateString);
	checkValueString(valueString);
	

	//convert value string to float
	float value;
	std::istringstream(valueString) >> value;

	//check for overflow by comparing to infinity
	if (value == std::numeric_limits<float>::infinity() 
		|| value == -std::numeric_limits<float>::infinity())
		throw std::runtime_error("Value overflowed.");


	//remove '-' and convert date to int 
	dateString.erase(std::remove(dateString.begin(), dateString.end(), '-'), dateString.end());
	size_t date;
	std::istringstream(dateString) >> date;

	//add to database
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

void BitcoinExchange::checkValue(float value)
{
	if (value < 0)
		throw std::runtime_error("Value is negative.");
	if (value > 1000)
		throw std::runtime_error("Value is to big.");
}

void BitcoinExchange::checkValue(int value)
{
	if (value < 0)
		throw std::runtime_error("Value is negative.");
	if (value > 1000)
		throw std::runtime_error("Value is to big.");
}

void BitcoinExchange::checkValueString(std::string valueString)
{
	for (size_t i = 0; i < valueString.size(); i++)
	{
		if (i == 0 && valueString[i] == '-')
			continue;
		if (!isdigit(valueString[i]) && valueString[i] != '.')
			throw std::runtime_error("Value is not only digits.");
	}
}

int BitcoinExchange::getCurrentYear()
{
    std::time_t t = std::time(NULL);
    std::tm* localTime = std::localtime(&t);
    return localTime->tm_year + 1900;
}



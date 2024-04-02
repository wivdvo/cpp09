#include <ctime>

#include "BitcoinExchange.hpp"

int BitcoinExchange::getCurrentYear()
{
    std::time_t t = std::time(NULL);
    std::tm* localTime = std::localtime(&t);
    return localTime->tm_year + 1900;
}

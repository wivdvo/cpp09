#include "BitcoinExchange.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
	try {
		if (argc != 2)
		{
			throw std::runtime_error("Need one file as argument!");
		}
		BitcoinExchange::doExchange(argv[1]);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

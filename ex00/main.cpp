#include "BitcoinExchange.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
	try
	{
		if (argc != 2)
		{

			BitcoinExchange::doExchange(NULL);

			//throw std::runtime_error("Need one file as argument!");
		}
		BitcoinExchange::doExchange(argv[1]);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

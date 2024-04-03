#include <exception>
#include <iostream>
#include <stdexcept>
#include "RPN.hpp"

int main(int argc, char** argv)
{
	try {
		if (argc != 2)
			throw std::runtime_error("Needs 1 argument. (\"1 + 1\")");
		if (argv[1] == NULL || argv[1][0] == 0)
			throw std::runtime_error("Invalid argument");
		RPN::doRPN(argv[1]);
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

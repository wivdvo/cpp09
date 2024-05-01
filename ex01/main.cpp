/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:09 by wvan-der          #+#    #+#             */
/*   Updated: 2024/05/01 13:19:34 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>
#include <stdexcept>
#include "RPN.hpp"

int main(int argc, char** argv)
{
	try {
		if (argc != 2)
			throw std::runtime_error("Needs 1 argument. e.g:(\"1 1 +\")");
		if (argv[1] == NULL || argv[1][0] == 0)
			throw std::runtime_error("Invalid argument");
		RPN::doRPN(argv[1]);
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

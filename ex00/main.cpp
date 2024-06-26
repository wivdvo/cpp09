/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:00:58 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/03 18:00:59 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		std::cerr << "Error: "<< e.what() << std::endl;
		return 1;
	}
	return 0;
}

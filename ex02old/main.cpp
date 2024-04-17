/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:28 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/12 10:36:19 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <exception>
#include <stdexcept>
#include <iostream>
int main(int ac, char** av)
{
	try {
		if (ac < 3)
			throw std::runtime_error("Needs at least two arguments");
		PmergeMe::doMerge(ac, av);

	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

}

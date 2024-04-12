/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:30 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/12 12:00:26 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	this->_vec = other._vec;
	this->_que = other._que;

	return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<int> PmergeMe::_vec;
std::vector<int> PmergeMe::_beforeSort;
std::deque<int> PmergeMe::_que;
int PmergeMe::nJacobs = 0;
int PmergeMe::lastJacobs = 1;
size_t PmergeMe::_jacobsNb[] = {
    3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 
    349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 
    357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123, 22906492245, 45812984491, 
    91625968981, 183251937963
};

void PmergeMe::doMerge(int ac, char** av)
{
	int temp;

	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		_vec.push_back(temp);
		_que.push_back(temp);
		_beforeSort.push_back(temp);
	}

	sortVec();
	//sortQue();
}

int PmergeMe::checkNb(std::string nbString)
{
	//std::cout << "checking " << nbString << std::endl;
	for (size_t i = 0; i < nbString.size(); i++)
	{
		if (!isdigit(nbString[i]))
			throw std::runtime_error("Invalid number (needs to be positive INT)");
	}

	//converting string to int and back to string
	//comparing original string to reconverted string
	//if they dont match overlow occured
	std::istringstream iss(nbString);
	std::ostringstream oss;
	int nb;
	iss >> nb;
	oss << nb;
	if (oss.str() != nbString)
		throw std::runtime_error("Number would overflow");
	return nb;
}

void PmergeMe::sortVec(void)
{
	printVec(splitVec(_vec));
}

std::vector<int> PmergeMe::splitVec(std::vector<int> vec)
{
	
	//basecase when two elements are left
	std::vector<int> ret;
	if (vec.size() <= 2)
	{
		if (vec.size() == 1)
		{
			ret.push_back(vec[0]);	
		}
		
		else if (vec[0] < vec[1])
		{
			ret.push_back(vec[0]);
			ret.push_back(vec[1]);
		}
		else
		{
			ret.push_back(vec[1]);
			ret.push_back(vec[0]);
		}
		return ret;
	}
	
	//split vec int two where a holds the bigger number of each pair([0][1])
	std::vector<int> a;
	std::vector<int> b;
	for (size_t i = 0; i < vec.size() - 2; i += 2)
	{
		if (i + 1 < vec.size())
		{
			if (vec[i] < vec[i+1])
			{
				a.push_back(vec[i+1]);
				b.push_back(vec[i]);
			}
			else 
			{
				a.push_back(vec[i]);
				b.push_back(vec[i+1]);            
			}
		}
		else
		{
			a.push_back(vec[i]);
		}
	}
	
	//split recursivly
	a = splitVec(a);
	b = splitVec(b);

	//do insertion	
	//b1 goes in front of a1
	a.insert(a.begin(), b[0]);
	int elementsAdded = 1;

	//get next jacobs nb to know which element to insert
		//size_t JacNb = nextJacobs(nJacobs);
	size_t JacNb = _jacobsNb[nJacobs];

	std::cout << "JacNB: " << JacNb << " nJacobs: " << nJacobs << std::endl;


	int elementsToInsert = JacNb - lastJacobs;
	std::vector<int>::iterator it;
	
	for (int i = 0 ;elementsToInsert > 0; i++, elementsToInsert--)
	{
		std::cout << "nJacobs: " <<nJacobs << " JacNb: "<< JacNb <<" i: " << i + 1 << std::endl;
		if (JacNb - (1 + i) < b.size())
		{
		
		
			std::cout << JacNb - (1 + i) << std::endl;
			std::cout << i << "\n\n\n";
			
			it = std::upper_bound(a.begin(), a.end(), b[JacNb - (1 + i)]);
			if (it != a.end())
			{
				a.insert(it, b[JacNb - (1 + i)]);
				elementsAdded++;
			}
			else
			{
				a.push_back(b[JacNb - (1 + i)]);
				elementsAdded++;
       		}
		}
	}

	lastJacobs = JacNb;
	nJacobs++;

	return a;
}

size_t PmergeMe::nextJacobs(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return nextJacobs(n - 1) + 2 * nextJacobs(n - 2);
}

void PmergeMe::printVec(std::vector<int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << i <<": "<< vec[i] << std::endl;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:37:25 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/22 17:23:36 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <algorithm>
#include <cstddef>
#include <deque>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

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
std::deque<int> PmergeMe::_que;
size_t PmergeMe::_jacobsNb[] = {
    1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 
    349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 
    357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123, 22906492245, 45812984491, 
    91625968981, 183251937963
};

size_t PmergeMe::biggestJacUsed = 0;

int PmergeMe::checkNb(std::string nbString)
{
	//check each number
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

void PmergeMe::printBefore(std::vector<int> vec)
{
	std::cout << "Before: ";

	if (vec.size() <= 5)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			std::cout << vec[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
}

void PmergeMe::printAfter(std::vector<int> vec)
{
	std::cout << "After:  ";

	if (vec.size() <= 5)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			std::cout << vec[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
}

void PmergeMe::doMerge(int ac, char** av)
{
	//fill vector
	clock_t start = clock();
	int temp;
	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		_vec.push_back(temp);
	}

	//start sorting the vector
	std::vector<int> resVec;
	resVec = sortVec(_vec);
	clock_t end = clock();
	double vecTime = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000);

	
	//fill deque
	start = clock();
	start = clock();
	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		_que.push_back(temp);
	}
	
	//start sotring the deque
	std::deque<int> resQue;
	resQue = sortQue(_que);
	end = clock();
	double queTime = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000);

	
	printBefore(_vec);
	printAfter(resVec);

	std::cout << std::endl;
	
	printTimes(vecTime, queTime, _vec.size());

	std::cout << std::endl;

	// std::cout << std::endl << "Final vec: " << std::endl;
	// printVecDebug(resVec);
	checkVecDebug(resVec);

	// std::cout << std::endl << "Final que: " << std::endl;
	// printQueDebug(resQue);
	checkQueDebug(resQue);
}

void PmergeMe::printTimes(double vecTime, double queTime, int n)
{
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Time to processe a range of " << n <<  " elements with std::vector<int>: " << vecTime  << " ms" << std::endl;
	std::cout << "Time to processe a range of " << n <<  " elements with std::deque<int>: " << queTime  << " ms" << std::endl;
}

void PmergeMe::checkVecDebug(std::vector<int> res)
{
	if (res.size() != _vec.size())
	{
		std::cout << "res: " << res.size() << " og: " << _vec.size() << std::endl;
		throw std::runtime_error("Lost elements");
	}
	
	for (size_t i = 1; i < res.size(); i++)
	{
		if (res[i-1] > res[i])
		{
			std::cout << "i: " << i << " nb: " << res[i] << std::endl;
			throw std::runtime_error("Not sorted");
		}
	}

	std::cout << "sorting vector: SUCCESS" << std::endl;
}

void PmergeMe::checkQueDebug(std::deque<int> res)
{
	if (res.size() != _vec.size())
	{
		std::cout << "res: " << res.size() << " og: " << _vec.size() << std::endl;
		throw std::runtime_error("Lost elements");
	}
	
	for (size_t i = 1; i < res.size(); i++)
	{
		if (res[i-1] > res[i])
		{
			std::cout << "i: " << i << " nb: " << res[i] << std::endl;
			throw std::runtime_error("Not sorted");
		}
	}

	std::cout << "sorting deque:  SUCCESS" << std::endl;
}

std::vector<int> PmergeMe::sortVec(std::vector<int> vec)
{
	//hardcode case for 2 or less elements
	if (vec.size() <= 2)
	{
		std::vector<int> ret;
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


	//check if there is an odd amount of elements
	//if so safe it to add it to A in the end
	int oddElement;
	bool hadOdd = false;
	if (vec.size() % 2 == 1)
	{
		oddElement = vec[vec.size() - 1];
		vec.pop_back();
		hadOdd = true;
		//std::cout << "had odd" << std::endl;
	}


	//create pairs and put bigger in A and smaller in B
	std::vector<int> a;
	std::vector<int> b;

	for (size_t i = 0; i < vec.size() - 1; i += 2)
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
	
	
	//split recursivly
	a = sortVec(a);
	b = sortVec(b);


	//do insertion	
	//b1 goes in front of a1
	a.insert(a.begin(), b[0]);


	//set values that are needed for the insertion
	int elementsToInsert = b.size() - 1;
	int elementsInserted = 1;
	size_t nJacNb = 1;
	size_t jacNb;
	size_t lastJacobs = 1;
	std::vector<int>::iterator it;
	
	
	//insert from current JacNb to last JacNb
	//repeat until all of b was inserted
	if (elementsToInsert > 3)
	{
		for (; elementsToInsert > 0; nJacNb++)
		{
			jacNb = _jacobsNb[nJacNb];
			it = a.end();
			for (size_t j = jacNb - 1; j > lastJacobs - 1 && elementsToInsert > 0; j--, elementsToInsert--)
			{
				if (j > b.size() - 1)
					j = b.size() - 1;
				it = std::upper_bound(a.begin(), a.end(), b[j]);
				if (it != a.end())
					it = std::upper_bound(a.begin(), it, b[j]);
				else
					it = std::upper_bound(a.begin(), a.begin(), b[j]);
				a.insert(it, b[j]);
				it--;
				elementsInserted++;
			}
			lastJacobs = jacNb;
		}
	}
	else
	{
		while (elementsToInsert > 0)
		{
			it = std::upper_bound(a.begin(), a.end(), b[elementsToInsert]);
			a.insert(it, b[elementsToInsert]);
			elementsInserted++;
			elementsToInsert--;
		}
	}
	

	//if there was odd amount of elements insert it in A
	if (hadOdd)
	{
		it = std::upper_bound(a.begin(), a.end(), oddElement);
		a.insert(it, oddElement);
	}

	return a;
}

std::deque<int> PmergeMe::sortQue(std::deque<int> que)
{
	//hardcode case for 2 or less elements
	if (que.size() <= 2)
	{
		std::deque<int> ret;
		if (que.size() == 1)
		{
			ret.push_back(que[0]);	
		}	
		else if (que[0] < que[1])
		{
			ret.push_back(que[0]);
			ret.push_back(que[1]);
		}
		else
		{
			ret.push_back(que[1]);
			ret.push_back(que[0]);
		}
		return ret;
	}


	//check if there is an odd amount of elements
	//if so safe it to add it to A in the end
	int oddElement;
	bool hadOdd = false;
	if (que.size() % 2 == 1)
	{
		oddElement = que[que.size() - 1];
		que.pop_back();
		hadOdd = true;
		//std::cout << "had odd" << std::endl;
	}


	//create pairs and put bigger in A and smaller in B
	std::deque<int> a;
	std::deque<int> b;

	for (size_t i = 0; i < que.size() - 1; i += 2)
	{
		if (que[i] < que[i+1])
		{
			a.push_back(que[i+1]);
			b.push_back(que[i]);
		}
		else 
		{
			a.push_back(que[i]);
			b.push_back(que[i+1]);            
		}
	}
	
	
	//split recursivly
	a = sortQue(a);
	b = sortQue(b);


	//do insertion	
	//b1 goes in front of a1
	a.insert(a.begin(), b[0]);


	//set values that are needed for the insertion
	int elementsToInsert = b.size() - 1;
	int elementsInserted = 1;
	size_t nJacNb = 1;
	size_t jacNb;
	size_t lastJacobs = 1;
	std::deque<int>::iterator it;
	
	
	//insert from current JacNb to last JacNb
	//repeat until all of b was inserted
	if (elementsToInsert > 3)
	{
		for (; elementsToInsert > 0; nJacNb++)
		{
			jacNb = _jacobsNb[nJacNb];
			it = a.end();
			for (size_t j = jacNb - 1; j > lastJacobs - 1 && elementsToInsert > 0; j--, elementsToInsert--)
			{
				if (j > b.size() - 1)
					j = b.size() - 1;
				it = std::upper_bound(a.begin(), a.end(), b[j]);
				if (it != a.end())
					it = std::upper_bound(a.begin(), it, b[j]);
				else
					it = std::upper_bound(a.begin(), a.begin(), b[j]);
				a.insert(it, b[j]);
				it--;
				elementsInserted++;
			}
			lastJacobs = jacNb;
		}
	}
	else
	{
		while (elementsToInsert > 0)
		{
			it = std::upper_bound(a.begin(), a.end(), b[elementsToInsert]);
			a.insert(it, b[elementsToInsert]);
			elementsInserted++;
			elementsToInsert--;
		}
	}
	

	//if there was odd amount of elements insert it in A
	if (hadOdd)
	{
		it = std::upper_bound(a.begin(), a.end(), oddElement);
		a.insert(it, oddElement);
	}

	return a;
}


void PmergeMe::printVecDebug(std::vector<int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << i + 1 <<": "<< vec[i] << std::endl;
	}
}

void PmergeMe::printQueDebug(std::deque<int> que)
{
	for (size_t i = 0; i < que.size(); i++)
	{
		std::cout << i + 1 <<": "<< que[i] << std::endl;
	}
}

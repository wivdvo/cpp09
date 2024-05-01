/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:37:25 by wvan-der          #+#    #+#             */
/*   Updated: 2024/05/01 13:17:24 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <algorithm>
#include <cstddef>
#include <deque>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <utility>
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
std::vector<int> PmergeMe::_resVec;
std::vector<int> PmergeMe::_ogAVec;

std::deque<int> PmergeMe::_que;
std::deque<int> PmergeMe::_resQue;
std::deque<int> PmergeMe::_ogAQue;

const size_t PmergeMe::_jacobsNb[] = {
    1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763,
    349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971,
    357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123, 22906492245, 45812984491,
    91625968981, 183251937963
};
int PmergeMe::comparisonCount = 0;

bool PmergeMe::Compare::operator()(int a, int b) {
	++comparisonCount;
	return a < b;
}

void PmergeMe::doMerge(int ac, char** av)
{
	int comparionsVec;
	int comparionsQue;

	//fill before
	std::vector<int> before;
	int temp;
	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		before.push_back(temp);
	}
	std::cout << "Before: " << std::endl;
	printVecDebug(before);
	
	checkDublicate(before);

	//fill vector
	clock_t start = clock();
	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		_vec.push_back(temp);
	}
	//sorting the vector
	sortVec(_vec);

	clock_t end = clock();
	double vecTime = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000);

	comparionsVec = comparisonCount;
	comparisonCount = 0;
	std::cout << "Final vec:" << std::endl;
	printVecDebug(_resVec);

	//fill deque
	start = clock();
	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		_que.push_back(temp);
	}
	//sotring the deque
	sortQue(_que);
	
	end = clock();
	double queTime = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000);

	comparionsQue = comparisonCount;
	std::cout << "Finale que:" << std::endl;
	printQueDebug(_resQue);


	printBefore(before);
	printAfter(_resVec, _resQue);
	std::cout << std::endl;
	printTimes(vecTime, queTime, _vec.size());
	std::cout << std::endl;


	std::cout << "Vec comparsons: " << comparionsVec << std::endl;
	std::cout << "Que comparsons: " << comparionsQue << std::endl;
	checkVec(_resVec);
	checkQue(_resQue);
}

void PmergeMe::sortVec(std::vector<int> vec)
{
	Chains chains;
	int oddElement = -1;

//	check for odd amount of elements
	if (vec.size() % 2 == 1)
	{
		oddElement = vec[vec.size() - 1];
		vec.pop_back();
	}


//	create pairs out of input vector
//	A gets bigger, B smaller
	for (size_t i = 0; i < vec.size() - 1; i+=2)
	{
		comparisonCount++;
		if (vec[i] < vec[i+1])
		{
			chains.a.push_back(vec[i+1]);
			chains.b.push_back(vec[i]);
		}
		else
		{
			chains.b.push_back(vec[i+1]);
			chains.a.push_back(vec[i]);
		}
	}

//	basecase
	if (vec.size() < 3)
	{
		_resVec.push_back(chains.b[0]);
		_resVec.push_back(chains.a[0]);

		if (oddElement != -1)
			_resVec.insert(std::upper_bound(_resVec.begin(), _resVec.end(), oddElement, Compare()), oddElement);
		return;
	}


//	add odd element
	if (oddElement != -1)
	{
		chains.b.push_back(oddElement);
	}

	sortVec(chains.a);

	// std::cout << "a: " << std::endl;
	// printVecDebug(chains.a);
	// std::cout << "b: " << std::endl;
	// printVecDebug(chains.b);
	// std::cout << "res: " << std::endl;
	// printVecDebug(_res);

	insertBVec(chains);
}

void PmergeMe::sortQue(std::deque<int> que)
{
	ChainsQ chainsQ;
	int oddElement = -1;

//	check for odd amount of elements
	if (que.size() % 2 == 1)
	{
		oddElement = que[que.size() - 1];
		que.pop_back();
	}


//	create pairs out of input quetor
//	A gets bigger, B smaller
	for (size_t i = 0; i < que.size() - 1; i+=2)
	{
		comparisonCount++;
		if (que[i] < que[i+1])
		{
			chainsQ.a.push_back(que[i+1]);
			chainsQ.b.push_back(que[i]);
		}
		else
		{
			chainsQ.b.push_back(que[i+1]);
			chainsQ.a.push_back(que[i]);
		}
	}

//	basecase
	if (que.size() < 3)
	{
		_resQue.push_back(chainsQ.b[0]);
		_resQue.push_back(chainsQ.a[0]);

		if (oddElement != -1)
			_resQue.insert(std::upper_bound(_resQue.begin(), _resQue.end(), oddElement, Compare()), oddElement);
		return;
	}


//	add odd element
	if (oddElement != -1)
	{
		chainsQ.b.push_back(oddElement);
	}

	sortQue(chainsQ.a);

	// std::cout << "a: " << std::endl;
	// printQueDebug(chainsQ.a);
	// std::cout << "b: " << std::endl;
	// printQueDebug(chainsQ.b);
	// std::cout << "res: " << std::endl;
	// printQueDebug(_res);

	insertBQue(chainsQ);
}

std::vector<int> PmergeMe::getOrderVec(int amount)
{
	std::vector<int> order;
	size_t lastJacNb = 0;
	size_t nJacNb = 0;
	size_t jacNb;
	size_t ogAmount = amount;

	while (amount > 0)
	{
		jacNb = _jacobsNb[nJacNb];
		if (jacNb > ogAmount)
			jacNb = ogAmount;
		size_t temp = jacNb;
		while (temp > lastJacNb && amount > 0)
		{
			//std::cout << "temp: " << temp << " amount: " << amount << std::endl;
			order.push_back(temp);
			temp--;
			amount--;
		}
		lastJacNb = jacNb;
		nJacNb++;
	}

	return order;
}

std::deque<int> PmergeMe::getOrderQue(int amount)
{
	std::deque<int> order;
	size_t lastJacNb = 0;
	size_t nJacNb = 0;
	size_t jacNb;
	size_t ogAmount = amount;

	while (amount > 0)
	{
		jacNb = _jacobsNb[nJacNb];
		if (jacNb > ogAmount)
			jacNb = ogAmount;
		size_t temp = jacNb;
		while (temp > lastJacNb && amount > 0)
		{
			//std::cout << "temp: " << temp << " amount: " << amount << std::endl;
			order.push_back(temp);
			temp--;
			amount--;
		}
		lastJacNb = jacNb;
		nJacNb++;
	}

	return order;
}

void PmergeMe::insertBVec(Chains chains)
{
	int element = 0;
	int toInsert = chains.b.size();
	int endIndex = 0;
	std::vector<int> order = getOrderVec(chains.b.size());
	int orderIndex = 0;
	std::vector<int>::iterator it;
	_ogAVec = _resVec;

	// std::cout << "a:" << std::endl;
	// printVecDebug(chains.a);
	// std::cout << "b:" << std::endl;
	// printVecDebug(chains.b);



//	b1 in front of a1
//	has to be Pair of res[0]
	element = chains.b[findPairVec(chains.a, _resVec, 0)];
	//std::cout << "Element1: " << element << std::endl;
	_resVec.insert(_resVec.begin(), element);
	toInsert--;
	orderIndex++;


//	insert rest
	for (; toInsert > 0; toInsert--, orderIndex++)
	{
//		check if element has patner
		if (order[orderIndex] <= _ogAVec.size())
		{
			element = chains.b[findPairVec(chains.a, _ogAVec, order[orderIndex]-1)];
			//std::cout << "Element2: " << element << std::endl;
			endIndex = findPairVec(_resVec, _ogAVec, order[orderIndex]-1);
			it = std::upper_bound(_resVec.begin(), _resVec.begin()+endIndex, element, Compare());
			_resVec.insert(it, element);
		}
		else
		{
			element = chains.b[chains.b.size()-1];
			//std::cout << "Element3: " << element << std::endl;
			it = std::upper_bound(_resVec.begin(), _resVec.end(), element, Compare());
			_resVec.insert(it, element);
		}
	}
}

void PmergeMe::insertBQue(ChainsQ chainsQ)
{
	int element = 0;
	int toInsert = chainsQ.b.size();
	int endIndex = 0;
	std::deque<int> order = getOrderQue(chainsQ.b.size());
	int orderIndex = 0;
	std::deque<int>::iterator it;
	_ogAQue = _resQue;

	// std::cout << "a:" << std::endl;
	// printVecDebug(chainsQ.a);
	// std::cout << "b:" << std::endl;
	// printVecDebug(chainsQ.b);



//	b1 in front of a1
//	has to be Pair of res[0]
	element = chainsQ.b[findPairQue(chainsQ.a, _resQue, 0)];
	//std::cout << "Element1: " << element << std::endl;
	_resQue.insert(_resQue.begin(), element);
	toInsert--;
	orderIndex++;


//	insert rest
	for (; toInsert > 0; toInsert--, orderIndex++)
	{
//		check if element has patner
		if (order[orderIndex] <= _ogAQue.size())
		{
			element = chainsQ.b[findPairQue(chainsQ.a, _ogAQue, order[orderIndex]-1)];
			//std::cout << "Element2: " << element << std::endl;
			endIndex = findPairQue(_resQue, _ogAQue, order[orderIndex]-1);
			it = std::upper_bound(_resQue.begin(), _resQue.begin()+endIndex, element, Compare());
			_resQue.insert(it, element);
		}
		else
		{
			element = chainsQ.b[chainsQ.b.size()-1];
			//std::cout << "Element3: " << element << std::endl;
			it = std::upper_bound(_resQue.begin(), _resQue.end(), element, Compare());
			_resQue.insert(it, element);
		}
	}
}

int PmergeMe::findPairVec(std::vector<int> vec, std::vector<int> toFindVec, int toFindIndex)
{
	int toFind = toFindVec[toFindIndex];

	if (toFind == -1)
	{
		return toFindIndex;
	}
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == toFind)
		{
			return i;
		}
	}
	return -1;
}

int PmergeMe::findPairQue(std::deque<int> que, std::deque<int> toFindQue, int toFindIndex)
{
	int toFind = toFindQue[toFindIndex];

	if (toFind == -1)
	{
		return toFindIndex;
	}
	for (size_t i = 0; i < que.size(); i++)
	{
		if (que[i] == toFind)
		{
			return i;
		}
	}
	return -1;
}


void PmergeMe::printVecDebug(std::vector<int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << i + 1 << ": "<< vec[i] << std::endl;
	}
	std::cout << std::endl;
}

void PmergeMe::printQueDebug(std::deque<int> que)
{
	for (size_t i = 0; i < que.size(); i++)
	{
		std::cout << i + 1 << ": "<< que[i] << std::endl;
	}
}


int PmergeMe::checkNb(std::string nbString)
{
//	check each number
	for (size_t i = 0; i < nbString.size(); i++)
	{
		if (!isdigit(nbString[i]))
			throw std::runtime_error("Invalid number (needs to be positive INT)");
	}


//	converting string to int and back to string
//	comparing original string to reconverted string
//	if they dont match overlow occured
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
	std::cout << std::endl << "Before:  ";

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

void PmergeMe::printAfter(std::vector<int> vec, std::deque<int> que)
{
	std::cout << std::endl << "After: " << std::endl;
	std::cout << "Vector:  ";
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

	std::cout << "Deque:   ";
	if (que.size() <= 5)
	{
		for (size_t i = 0; i < que.size(); i++)
		{
			std::cout << que[i] << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			std::cout << que[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
}

void PmergeMe::printTimes(double vecTime, double queTime, int n)
{
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Time to processe a range of " << n <<  " elements with std::vector<int>: " << vecTime  << " ms" << std::endl;
	std::cout << "Time to processe a range of " << n <<  " elements with std::deque<int>: " << queTime  << " ms" << std::endl;
}

void PmergeMe::checkVec(std::vector<int> res)
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

	for (size_t i = 1; i < res.size(); i++)
	{
		if (res[i-1] == res[i])
		{
			std::cout << "i: " << i << " nb: " << res[i] << std::endl;
			throw std::runtime_error("Dublicate created");
		}
	}

	std::cout << "sorting vector: SUCCESS" << std::endl;
}

void PmergeMe::checkQue(std::deque<int> res)
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

	for (size_t i = 1; i < res.size(); i++)
	{
		if (res[i-1] == res[i])
		{
			std::cout << "i: " << i << " nb: " << res[i] << std::endl;
			throw std::runtime_error("Dublicate created");
		}
	}

	std::cout << "sorting deque:  SUCCESS" << std::endl;
}

void PmergeMe::checkDublicate(std::vector<int> input)
{
	std::sort(input.begin(), input.end());

	if (std::adjacent_find(input.begin(), input.end()) != input.end())
		throw std::runtime_error("Dublicate in input");
}
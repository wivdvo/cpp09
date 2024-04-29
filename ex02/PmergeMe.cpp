/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:37:25 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/29 17:45:40 by wvan-der         ###   ########.fr       */
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
std::vector<int> PmergeMe::_res;
std::vector<int> PmergeMe::_ogA;
std::deque<int> PmergeMe::_que;
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
	//fill vector
	clock_t start = clock();
	int temp;
	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		_vec.push_back(temp);
	}
	//sorting the vector
	std::vector<int> resVec;

	sortVec(_vec);

	std::cout << "final" << std::endl;
	printVecDebug(_res);


	clock_t end = clock();
	double vecTime = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000);


	//fill deque
	start = clock();
	for (int i = 1; i < ac; i++)
	{
		temp = checkNb(av[i]);
		_que.push_back(temp);
	}
	//sotring the deque
	std::deque<int> resQue;
	resQue = sortQue(_que);
	end = clock();
	double queTime = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000);


	printBefore(_vec);
	printAfter(resVec, resQue);
	std::cout << std::endl;
	printTimes(vecTime, queTime, _vec.size());
	std::cout << std::endl;

	std::cout << "Finale Vec:" << std::endl;
	printVecDebug(resVec);
	//std::cout << std::endl << "Finale que:" << std::endl;
	//printQueDebug(resQue);

	std::cout << "Comparions " << comparisonCount << std::endl;
	checkVec(resVec);
	//checkQue(resQue);
}

void PmergeMe::sortVec(std::vector<int> vec)
{
	std::cout << "begin" << std::endl;
	Chains chains;
	int oddElement = -1;

//	check for odd amount of elements
	if (vec.size() % 2 == 1)
	{
		oddElement = vec[vec.size() - 1];
		vec.pop_back();
	}
	

//	create pairs out of input vector
	for (size_t i = 0; i < vec.size() - 1; i+=2)
	{
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
		std::cout << "basecase" << std::endl;
		_res.push_back(chains.b[0]);
		_res.push_back(chains.a[0]);

		if (oddElement != -1)
			_res.insert(std::upper_bound(_res.begin(), _res.end(), oddElement), oddElement);
		return;
	}


//	add odd element
	if (oddElement != -1)
	{
		chains.b.push_back(oddElement);
		chains.a.push_back(-1);
	}
	sortVec(chains.a);
	
	std::cout << "a: " << std::endl;
	printVecDebug(chains.a);
	std::cout << "b: " << std::endl;
	printVecDebug(chains.b);
	std::cout << "res: " << std::endl;
	printVecDebug(_res);

	insertB(chains);
}

std::vector<int> getOrder(int amount)
{
	std::vector<int> order;
	if (amount == 3)
	{
		order.push_back(1);
		order.push_back(3);
		order.push_back(2);
		return order;
	}
	if (amount == 2)
	{
		order.push_back(1);
		order.push_back(2);
		return order;
	}
	if (amount == 1)
	{
		order.push_back(1);
	}
	
}

void PmergeMe::sort3orLess(Chains chains)
{
	int element = 0;
	int toInsert = chains.b.size();
	int endIndex = 0;
	std::vector<int> order = getOrder(chains.b.size());
	int orderIndex = 0;
	std::vector<int>::iterator it;


//	b1 in front of a1
//	has to be Pair of res[0]
	element = chains.b[findPair(chains.a, _res, 0)];
	std::cout << "toInsert: " << toInsert << " Element: " << element << " endIndex: " << endIndex << std::endl;
	_res.insert(_res.begin(), element);
	toInsert--;
	orderIndex++;
	
	
//	insert rest
	for (; toInsert > 0; toInsert--, orderIndex++)
	{
		//check if element has patner
		std::cout << "order: " << order[orderIndex] << std::endl;
		if (order[orderIndex] >= _ogA.size())
		{
			std::cout << "in if" << std::endl;
			//endIndex is infront of partner
			element = chains.b[findPair(chains.a, _res, toInsert)];
			endIndex = findPair(chains.a, _res, toInsert);
			std::cout << "if  toInsert: " << toInsert << " Element: " << element << " endIndex: " << endIndex << std::endl;
			//insert
		}
		else
		{
			element = chains.b[chains.b.size()-1];
			it = std::upper_bound(_res.begin(), _res.end(), element);
			std::cout << "else  toInsert: " << toInsert << " Element: " << element << " endIndex: " << endIndex << std::endl;
			_res.insert(it, element);
		}
	}
}

void PmergeMe::insertB(Chains chains)
{
	int elementsToInsert = chains.b.size();
	int nJacNb = 1;
	size_t jacNb;
	size_t lastJacobs = 1;
	size_t currIndex;
	size_t lastIndex;
	int element;
	std::vector<int>::iterator it;
	int endOffset;

	_ogA = _res;


	if (chains.b.size() <= 3)
		sort3orLess(chains);

	// std::cout << "element " << chains.b[findPair(chains.a, _res[0], 0)] << std::endl;
	// _res.insert(_res.begin(), chains.b[findPair(chains.a, chains.a[0], 0)]);
	// elementsToInsert--;
	// // std::cout << "before loops" << std::endl;
	// // printVecDebug(_res);
	// if (elementsToInsert < 3)
	// {
	// 	std::cout << "IF" << std::endl;
	// 	currIndex = 3;
	// 	for (; elementsToInsert > 0; elementsToInsert--)
	// 	{
	// 		//case were b3 does not have patner
	// 		if (_res.size() < currIndex)
	// 		{
	// 			element = chains.b[currIndex-1];
	// 		}
	// 		else {
	// 			element = chains.b[findPair(chains.a, chains.a[elementsToInsert], elementsToInsert)];
	// 		}
	// 		endOffset = findPair(_res, chains.a[elementsToInsert], elementsToInsert);
	// 		it = std::upper_bound(_res.begin(), _res.begin() + endOffset, element, Compare());
	// 		std::cout << "element: " << element<< " elementsToInsert: " << elementsToInsert << " end offset: " << endOffset << std::endl;
	// 		printVecDebug(_res);
	// 		_res.insert(it, element);
	// 	}
	// }
	// else
	// {
	// 	std::cout << "ELSE" << std::endl;
	// 	for (; elementsToInsert > 0; nJacNb++)
	// 	{
	// 		jacNb = _jacobsNb[nJacNb];
	// 		lastIndex = lastJacobs - 1;
	// 		setCurrentIndex(jacNb, chains.b.size(), currIndex);
	// 		for (;currIndex > lastIndex && elementsToInsert > 0; currIndex--, elementsToInsert--)
	// 		{
	// 			element = chains.b[currIndex];
	// 			_res.insert(std::upper_bound(_res.begin(), _res.end(), element, Compare()), element);
	// 		}
	// 		lastJacobs = jacNb;
	// 	}
	// }
}

int PmergeMe::findPair(std::vector<int> vec, std::vector<int> toFindVec, int toFindIndex)
{
	int toFind = toFindVec[toFindIndex];
	
	if (toFind == -1)
	{
		std::cout << "to find is -1" << std::endl;
		return toFindIndex;
	}
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == toFind)
		{
			std::cout << "to find: " << toFind << " pair index: " << i << std::endl;
			return i;
		}
	}
	std::cout << "could not find pair" << std::endl;
	return -1;
}


void PmergeMe::setCurrentIndex(size_t jacNb, size_t size, size_t& currIndex)
{
		if (jacNb > size)
		{
			currIndex = size - 1;
		}
		else
		{
			currIndex = jacNb - 1;	
		}
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
				//it = std::upper_bound(a.begin(), a.end(), b[j]);
				if (it != a.end())
					it = std::upper_bound(a.begin(), it, b[j]);
				else
					it = std::upper_bound(a.begin(), a.end(), b[j]);
				a.insert(it, b[j]);
				it--;
				elementsInserted++;
			}
			lastJacobs = jacNb;
		}
	}
	else
	{
		while (elementsToInsert > 0 && elementsToInsert < (int)b.size())
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
	//std::cout << "a: " << std::endl;
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

	std::cout << "sorting deque:  SUCCESS" << std::endl;
}

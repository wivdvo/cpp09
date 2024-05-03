/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:18 by wvan-der          #+#    #+#             */
/*   Updated: 2024/05/02 13:56:03 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <climits>

RPN::RPN(void) {}

RPN::RPN(const RPN& other)
{
	*this = other;
}

RPN& RPN::operator=(const RPN& other)
{
	this->_stack = other._stack;

	return *this;
}

RPN::~RPN() {}

std::stack<int> RPN::_stack;

void RPN::doRPN(std::string input)
{
	checkInput(input);

	//remove all spaces from input
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

	for (size_t i = 0; i < input.size(); i++)
	{
		if (std::isdigit(input[i]))
		{
			_stack.push(input[i] - 48);
		}
		else
		{
			if (input[i] == '+')
				add();
			if (input[i] == '-')
				sub();
			if (input[i] == '*')
				mult();
			if (input[i] == '/')
				div();
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Invalid input.");
	std::cout << _stack.top() << std::endl;
}

void RPN::div()
{
	long a = 0;
	long b = 0;
	long temp;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	if (a == 0)
		throw std::runtime_error("Division by 0 is undifined.");
	temp = b / a;
	if (temp >= INT_MAX || temp <= INT_MIN)
		throw std::runtime_error("Overflow");
	_stack.push(b / a);
}

void RPN::mult()
{
	long a = 0;
	long b = 0;
	long temp;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	temp = a * b;
	if (temp >= INT_MAX || temp <= INT_MIN)
		throw std::runtime_error("Overflow");
	_stack.push(a * b);
}

void RPN::sub()
{
	long a = 0;
	long b = 0;
	long temp;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	temp = b - a;
	if (temp >= INT_MAX || temp <= INT_MIN)
		throw std::runtime_error("Overflow");
	_stack.push(b - a);
}

void RPN::add()
{
	long a = 0;
	long b = 0;
	long temp;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
	else {
		throw std::runtime_error("Invalid input");
	}
	temp = a + b;
	if (temp >= INT_MAX || temp <= INT_MIN)
		throw std::runtime_error("Overflow");
	_stack.push(a + b);
}

void RPN::checkInput(std::string input)
{
	//every even char has to be number or operator every odd char has to be space
	for (size_t i = 0; i < input.size(); i++)
	{
		if (i % 2 == 0)
		{
			if (!validChar(input[i]))
				throw std::runtime_error("Invalid format. should be (\"1 1 +\")");
		}
		else
		{
			if (input[i] != ' ')
				throw std::runtime_error("Invalid format. should be (\"1 1 +\")");
		}
	}
}

bool RPN::validChar(char c)
{
	if (std::isdigit(c) || c == '*' || c == '/' || c == '+' || c == '-')
		return true;
	else
	 	return false;
}

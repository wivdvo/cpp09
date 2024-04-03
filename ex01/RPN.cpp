/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:18 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/03 18:01:19 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>

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
	std::cout << _stack.top() << std::endl;
}

void RPN::div()
{
	int a = 0;
	int b = 0;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
	if (a == 0)
		throw std::runtime_error("Division by 0 is undifined.");
	_stack.push(b / a);
}

void RPN::mult()
{
	int a = 0;
	int b = 0;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
	_stack.push(a * b);
}

void RPN::sub()
{
	int a = 0;
	int b = 0;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
	_stack.push(b - a);
}

void RPN::add()
{
	int a = 0;
	int b = 0;
	if (!_stack.empty())
	{
		a = _stack.top();
		_stack.pop();
	}
	if (!_stack.empty())
	{
		b = _stack.top();
		_stack.pop();
	}
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
				throw std::runtime_error("Invalid format. (\"1 + 1\")");
		}
		else
		{
			if (input[i] != ' ')
				throw std::runtime_error("Invalid format. (\"1 + 1\")");
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

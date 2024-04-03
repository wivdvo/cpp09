/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:23 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/03 18:01:24 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>

class RPN
{
	public:
		static void doRPN(std::string input);

	private:
		RPN(void);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		static void checkInput(std::string input);
		static bool validChar(char c);
		static void add(void);
		static void sub(void);
		static void mult(void);
		static void div(void);

		static std::stack<int> _stack;

};

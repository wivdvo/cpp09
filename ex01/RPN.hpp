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

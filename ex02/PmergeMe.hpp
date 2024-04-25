/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:33 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/25 18:54:01 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <string>

struct Chains
{
	std::vector<int> a;
	std::vector<int> b;
	std::vector<int> n;
};

class PmergeMe
{
	public:
		static void doMerge(int ac, char** av);

	private:

		PmergeMe(void);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		static int checkNb(std::string nb);
		static void printBefore(std::vector<int> before);
		static void printAfter(std::vector<int> vec, std::deque<int> que);
		static void printTimes(double vecTime, double queTime, int n);

		static Chains sortVec(Chains chains, char mode);

		
		
		static void prepareVec(std::vector<int> vec);
		static Chains sortA(Chains chains);
		static Chains sortB(Chains chains);
		static void doVecInsertion(Chains chains);




		static std::vector<int> sortVec(std::vector<int> a, std::vector<int> b, int oddElement, char mode);
		static void printVec(std::vector<int> vec);
		static void checkVec(std::vector<int> vec);
		static void printVecDebug(std::vector<int> vec);

		static std::deque<int> sortQue(std::deque<int> que);
		static void printQue(std::deque<int> que);
		static void checkQue(std::deque<int> que);
		static void printQueDebug(std::deque<int> que);
		
		static std::vector<int> _vec;
		static std::deque<int> _que;
		static const size_t _jacobsNb[];
		static int comparisonCount;




		struct Compare
		{
			bool operator()(int a, int b);
		};
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:33 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/22 17:42:49 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <string>

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
		
		static std::vector<int> sortVec(std::vector<int> vec);
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
};

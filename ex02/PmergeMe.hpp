/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:33 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/22 13:51:36 by wvan-der         ###   ########.fr       */
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
		static std::vector<int> sortVec(std::vector<int> vec);
		static std::deque<int> sortQue(void);

		static void printVec(std::vector<int> vec);
		static void checkRes(std::vector<int> res);
		static int calcInsertionArea(int nJacNb);
		static void setPosForInsertion(int& beginIndex, int& endIndex, int elementsInserted, int nJacNb, int j);

		static std::vector<int> _vec;
		static std::deque<int> _que;
		//static std::vector<int> _beforeSort;
		static size_t _jacobsNb[];

		static size_t biggestJacUsed;
};

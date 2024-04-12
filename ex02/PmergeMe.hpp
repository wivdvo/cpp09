/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:33 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/12 10:39:24 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
	public:
		static void doMerge(int ac, char** av);
		static size_t nextJacobs(int n);

	private:
		PmergeMe(void);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		static int checkNb(std::string nb);
		static void sortVec(void);
		static void sortQue(void);
		static std::vector<int> splitVec(std::vector<int> prevVec);

		static void printVec(std::vector<int> vec);

		static std::vector<int> _vec;
		static std::deque<int> _que;
		static std::vector<int> _beforeSort;
		static size_t _jacobsNb[];
		static int nJacobs;
		static int lastJacobs;
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:33 by wvan-der          #+#    #+#             */
/*   Updated: 2024/04/30 14:34:39 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <string>

struct Chains
{
	std::vector<int> a;
	std::vector<int> b;
};

struct ChainsQ
{
	std::deque<int> a;
	std::deque<int> b;
};

class PmergeMe
{
	public:
		static void 				doMerge(int ac, char** av);

	private:

		PmergeMe(void);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		static int 					checkNb(std::string nb);
		static void 				printBefore(std::vector<int> before);
		static void 				printAfter(std::vector<int> vec, std::deque<int> que);
		static void 				printTimes(double vecTime, double queTime, int n);

		static void 				sortVec(std::vector<int> vec);
		static void 				insertBVec(Chains chains);
		static int 					findPairVec(std::vector<int> vec, std::vector<int> toFindVec, int toFindIndex);
		static std::vector<int> 	getOrderVec(int amount);
		static void 				printVec(std::vector<int> vec);
		static void 				checkVec(std::vector<int> vec);
		static void 				printVecDebug(std::vector<int> vec);


		static void 				sortQue(std::deque<int> que);
		static void 				insertBQue(ChainsQ chainsQ);
		static int 					findPairQue(std::deque<int> que, std::deque<int> toFindQue, int toFindIndex);
		static std::deque<int> 		getOrderQue(int amount);
		static void 				printQue(std::deque<int> que);
		static void 				checkQue(std::deque<int> que);
		static void 				printQueDebug(std::deque<int> que);
		
		static std::vector<int> 	_vec;
		static std::vector<int> 	_resVec;
		static std::vector<int> 	_ogAVec;
		
		static std::deque<int> 		_que;
		static std::deque<int> 		_resQue;
		static std::deque<int> 		_ogAQue;
		
		static const size_t 		_jacobsNb[];
		static int 					comparisonCount;

		struct Compare
		{
			bool operator()(int a, int b);
		};
};

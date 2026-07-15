#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
	private:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		static void fordJohnsonSortVec(std::vector<int>& arr);
		static void fordJohnsonSortDeq(std::deque<int>& arr);

	public:
		static void sortAndMeasure(const std::vector<int>& input);
};

#endif

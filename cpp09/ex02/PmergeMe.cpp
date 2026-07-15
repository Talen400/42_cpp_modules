#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <sys/time.h>
#include <utility>

static double getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

static void fordJohnsonSortVecImpl(std::vector<int>& arr) {
	int n = arr.size();
	if (n <= 1)
		return;

	bool hasStraggler = (n % 2 == 1);
	int straggler = hasStraggler ? arr[n - 1] : 0;
	int pairCount = n / 2;

	std::vector<std::pair<int,int> > pairs(pairCount);
	for (int i = 0; i < pairCount; i++) {
		int a = arr[2 * i];
		int b = arr[2 * i + 1];
		if (a > b)
			std::swap(a, b);
		pairs[i] = std::make_pair(a, b);
	}

	for (int i = 1; i < pairCount; i++) {
		std::pair<int,int> key = pairs[i];
		int j = i - 1;
		while (j >= 0 && pairs[j].second > key.second) {
			pairs[j + 1] = pairs[j];
			j--;
		}
		pairs[j + 1] = key;
	}

	std::vector<int> main;
	std::vector<int> pend;
	main.reserve(pairCount + pairCount + 1);
	pend.reserve(pairCount);

	for (int i = 0; i < pairCount; i++) {
		main.push_back(pairs[i].second);
		pend.push_back(pairs[i].first);
	}

	fordJohnsonSortVecImpl(main);

	main.insert(main.begin(), pend[0]);

	std::vector<int> jacob;
	jacob.push_back(1);
	jacob.push_back(1);
	while (jacob.back() < pairCount) {
		int sz = jacob.size();
		jacob.push_back(jacob[sz - 1] + 2 * jacob[sz - 2]);
	}

	std::vector<bool> inserted(pairCount, false);
	inserted[0] = true;

	for (size_t k = 2; k < jacob.size(); k++) {
		int end = jacob[k - 1];
		int start = jacob[k] - 1;
		if (start >= pairCount)
			start = pairCount - 1;
		if (end < 1)
			end = 1;
		if (start < end)
			continue;

		for (int i = start; i >= end; i--) {
			if (inserted[i])
				continue;

			std::vector<int>::iterator pos =
				std::lower_bound(main.begin(), main.end(), pend[i]);
			main.insert(pos, pend[i]);
			inserted[i] = true;
		}
	}

	for (int i = 1; i < pairCount; i++) {
		if (inserted[i])
			continue;

		std::vector<int>::iterator pos =
			std::lower_bound(main.begin(), main.end(), pend[i]);
		main.insert(pos, pend[i]);
	}

	if (hasStraggler) {
		std::vector<int>::iterator pos =
			std::lower_bound(main.begin(), main.end(), straggler);
		main.insert(pos, straggler);
	}

	arr = main;
}

void PmergeMe::fordJohnsonSortVec(std::vector<int>& arr) {
	fordJohnsonSortVecImpl(arr);
}

static void fordJohnsonSortDeqImpl(std::deque<int>& arr) {
	int n = arr.size();
	if (n <= 1)
		return;

	bool hasStraggler = (n % 2 == 1);
	int straggler = hasStraggler ? arr[n - 1] : 0;
	int pairCount = n / 2;

	std::vector<std::pair<int,int> > pairs(pairCount);
	for (int i = 0; i < pairCount; i++) {
		int a = arr[2 * i];
		int b = arr[2 * i + 1];
		if (a > b)
			std::swap(a, b);
		pairs[i] = std::make_pair(a, b);
	}

	for (int i = 1; i < pairCount; i++) {
		std::pair<int,int> key = pairs[i];
		int j = i - 1;
		while (j >= 0 && pairs[j].second > key.second) {
			pairs[j + 1] = pairs[j];
			j--;
		}
		pairs[j + 1] = key;
	}

	std::deque<int> main;
	std::vector<int> pend(pairCount);

	for (int i = 0; i < pairCount; i++) {
		main.push_back(pairs[i].second);
		pend[i] = pairs[i].first;
	}

	fordJohnsonSortDeqImpl(main);

	main.push_front(pend[0]);

	std::vector<int> jacob;
	jacob.push_back(1);
	jacob.push_back(1);
	while (jacob.back() < pairCount) {
		int sz = jacob.size();
		jacob.push_back(jacob[sz - 1] + 2 * jacob[sz - 2]);
	}

	std::vector<bool> inserted(pairCount, false);
	inserted[0] = true;

	for (size_t k = 2; k < jacob.size(); k++) {
		int end = jacob[k - 1];
		int start = jacob[k] - 1;
		if (start >= pairCount)
			start = pairCount - 1;
		if (end < 1)
			end = 1;
		if (start < end)
			continue;

		for (int i = start; i >= end; i--) {
			if (inserted[i])
				continue;

			std::deque<int>::iterator pos =
				std::lower_bound(main.begin(), main.end(), pend[i]);
			main.insert(pos, pend[i]);
			inserted[i] = true;
		}
	}

	for (int i = 1; i < pairCount; i++) {
		if (inserted[i])
			continue;

		std::deque<int>::iterator pos =
			std::lower_bound(main.begin(), main.end(), pend[i]);
		main.insert(pos, pend[i]);
	}

	if (hasStraggler) {
		std::deque<int>::iterator pos =
			std::lower_bound(main.begin(), main.end(), straggler);
		main.insert(pos, straggler);
	}

	arr = main;
}

void PmergeMe::fordJohnsonSortDeq(std::deque<int>& arr) {
	fordJohnsonSortDeqImpl(arr);
}

void PmergeMe::sortAndMeasure(const std::vector<int>& input) {
	std::cout << "Before: ";
	for (size_t i = 0; i < input.size(); i++) {
		std::cout << input[i];
		if (i + 1 < input.size())
			std::cout << " ";
	}
	std::cout << std::endl;

	std::vector<int> vec(input);
	double startVec = getTime();
	fordJohnsonSortVec(vec);
	double endVec = getTime();

	std::cout << "After: ";
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i];
		if (i + 1 < vec.size())
			std::cout << " ";
	}
	std::cout << std::endl;

	std::deque<int> deq(input.begin(), input.end());
	double startDeq = getTime();
	fordJohnsonSortDeq(deq);
	double endDeq = getTime();

	double timeVec = endVec - startVec;
	double timeDeq = endDeq - startDeq;

	std::cout.precision(5);
	std::cout << "Time to process a range of " << input.size()
			  << " elements with std::vector : " << std::fixed << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << input.size()
			  << " elements with std::deque : " << std::fixed << timeDeq << " us" << std::endl;
}

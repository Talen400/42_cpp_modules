#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <sys/time.h>

static double getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

static void insertSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

static void mergeSortVector(std::vector<int>& arr) {
    if (arr.size() <= 16) {
        insertSort(arr);
        return;
    }

    size_t mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    mergeSortVector(left);
    mergeSortVector(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(), arr.begin());
}

static void insertSortDeque(std::deque<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

static void mergeSortDeque(std::deque<int>& arr) {
    if (arr.size() <= 16) {
        insertSortDeque(arr);
        return;
    }

    size_t mid = arr.size() / 2;
    std::deque<int> left(arr.begin(), arr.begin() + mid);
    std::deque<int> right(arr.begin() + mid, arr.end());

    mergeSortDeque(left);
    mergeSortDeque(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(), arr.begin());
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& arr) {
    mergeSortVector(arr);
}

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr) {
    mergeSortDeque(arr);
}

void PmergeMe::sortAndMeasure(const std::vector<int>& input) {
    std::cout << "Before: ";
    for (size_t i = 0; i < input.size(); i++)
        std::cout << input[i] << " ";
    std::cout << std::endl;

    std::vector<int> vec(input);
    double startVec = getTime();
    mergeInsertSortVector(vec);
    double endVec = getTime();

    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::deque<int> deq(input.begin(), input.end());
    double startDeq = getTime();
    mergeInsertSortDeque(deq);
    double endDeq = getTime();

    double timeVec = endVec - startVec;
    double timeDeq = endDeq - startDeq;

    std::cout.precision(5);
    std::cout << "Time to process a range of " << input.size()
              << " elements with std::vector : " << std::fixed << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << input.size()
              << " elements with std::deque : " << std::fixed << timeDeq << " us" << std::endl;
}

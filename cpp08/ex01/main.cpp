#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main() {
    std::cout << "=== Basic test from subject ===" << std::endl;
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << "shortestSpan: " << sp.shortestSpan() << " (expected: 2)" << std::endl;
    std::cout << "longestSpan:  " << sp.longestSpan() << " (expected: 14)" << std::endl;

    std::cout << "\n=== Exception: not enough numbers ===" << std::endl;
    Span small(5);
    small.addNumber(42);
    try {
        small.shortestSpan();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Exception: full span ===" << std::endl;
    Span tiny(1);
    tiny.addNumber(1);
    try {
        tiny.addNumber(2);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Big test: 20000 numbers ===" << std::endl;
    srand(time(NULL));

    Span big(20000);
    for (int i = 0; i < 20000; i++)
        big.addNumber(rand());

    std::cout << "shortestSpan: " << big.shortestSpan() << std::endl;
    std::cout << "longestSpan:  " << big.longestSpan() << std::endl;

    std::cout << "\n=== Range add with iterators ===" << std::endl;
    std::vector<int> vi;
    vi.push_back(10);
    vi.push_back(20);
    vi.push_back(30);
    vi.push_back(40);
    vi.push_back(50);

    Span range(5);
    range.addNumber(vi.begin(), vi.end());
    std::cout << "size after range add: " << range.size() << " (expected: 5)" << std::endl;
    std::cout << "shortestSpan: " << range.shortestSpan() << " (expected: 10)" << std::endl;
    std::cout << "longestSpan:  " << range.longestSpan() << " (expected: 40)" << std::endl;

    std::cout << "\n=== Copy constructor ===" << std::endl;
    Span copy(big);
    std::cout << "copy size: " << copy.size() << " (expected: 20000)" << std::endl;
    std::cout << "copy shortestSpan: " << copy.shortestSpan() << std::endl;

    std::cout << "\n=== Assignment ===" << std::endl;
    Span assigned(0);
    assigned = big;
    std::cout << "assigned size: " << assigned.size() << " (expected: 20000)" << std::endl;
    std::cout << "assigned longestSpan: " << assigned.longestSpan() << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main() {
    std::cout << "=== Vector ===" << std::endl;
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(20);

    try {
        std::vector<int>::iterator it = easyfind(v, 20);
        std::cout << "Found: " << *it << " at position "
                  << std::distance(v.begin(), it) << std::endl;

        it = easyfind(v, 99);
        std::cout << "Found: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== List ===" << std::endl;
    std::list<int> l;
    l.push_back(5);
    l.push_back(15);
    l.push_back(25);

    try {
        std::list<int>::iterator it = easyfind(l, 15);
        std::cout << "Found: " << *it << std::endl;

        it = easyfind(l, 99);
        std::cout << "Found: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Deque ===" << std::endl;
    std::deque<int> d;
    d.push_back(100);
    d.push_back(200);
    d.push_back(300);

    try {
        std::deque<int>::iterator it = easyfind(d, 100);
        std::cout << "Found: " << *it << std::endl;

        it = easyfind(d, 999);
        std::cout << "Found: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Const container ===" << std::endl;
    const std::vector<int> cv(v);
    try {
        std::vector<int>::const_iterator it = easyfind(cv, 30);
        std::cout << "Found: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

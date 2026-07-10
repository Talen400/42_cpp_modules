#include <iostream>
#include <string>
#include "Array.hpp"

struct Test {
    int n;
    Test() : n(42) {}
};

int main() {
    std::cout << "=== Empty array ===" << std::endl;
    Array<int> empty;
    std::cout << "size: " << empty.size() << std::endl;

    std::cout << "\n=== Int array ===" << std::endl;
    Array<int> arr(5);
    for (unsigned int i = 0; i < arr.size(); i++)
        arr[i] = i * 2;
    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;

    std::cout << "\n=== Copy constructor (deep copy) ===" << std::endl;
    Array<int> copy(arr);
    copy[0] = 99;
    std::cout << "arr[0] = " << arr[0] << " (should be 0)" << std::endl;
    std::cout << "copy[0] = " << copy[0] << " (should be 99)" << std::endl;

    std::cout << "\n=== Assignment operator (deep copy) ===" << std::endl;
    Array<int> assigned(3);
    assigned = arr;
    std::cout << "assigned size: " << assigned.size() << " (should be 5)" << std::endl;
    assigned[1] = 77;
    std::cout << "arr[1] = " << arr[1] << " (should be 2)" << std::endl;
    std::cout << "assigned[1] = " << assigned[1] << " (should be 77)" << std::endl;

    std::cout << "\n=== Out of bounds test ===" << std::endl;
    try {
        arr[10] = 42;
        std::cout << "NO EXCEPTION (should not print)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught (expected)" << std::endl;
    }

    std::cout << "\n=== String array ===" << std::endl;
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "Templates";
    for (unsigned int i = 0; i < strings.size(); i++)
        std::cout << "strings[" << i << "] = " << strings[i] << std::endl;

    std::cout << "\n=== Const array ===" << std::endl;
    const Array<std::string> constStrings(strings);
    for (unsigned int i = 0; i < constStrings.size(); i++)
        std::cout << "constStrings[" << i << "] = " << constStrings[i] << std::endl;

    std::cout << "\n=== Self-assignment ===" << std::endl;
    Array<int> self(3);
    self[0] = 1;
    self[1] = 2;
    self[2] = 3;
	Array<int> &selfRef = self;
	self = selfRef;
    for (unsigned int i = 0; i < self.size(); i++)
        std::cout << "self[" << i << "] = " << self[i] << std::endl;

    std::cout << "\n=== Default initialized values ===" << std::endl;
    Array<Test> tests(3);
    for (unsigned int i = 0; i < tests.size(); i++)
        std::cout << "tests[" << i << "].n = " << tests[i].n << " (should be 42)" << std::endl;

    return 0;
}

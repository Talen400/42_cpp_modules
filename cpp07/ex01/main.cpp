#include <iostream>
#include "iter.hpp"

template <typename T>
void print(T const& x) {
    std::cout << x << " ";
}

template <typename T>
void increment(T& x) {
    x++;
}

int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    size_t intLen = sizeof(intArr) / sizeof(intArr[0]);

    std::cout << "intArr: ";
    iter(intArr, intLen, print<int>);
    std::cout << std::endl;

    iter(intArr, intLen, increment<int>);

    std::cout << "intArr after increment: ";
    iter(intArr, intLen, print<int>);
    std::cout << std::endl;

    std::string strArr[] = {"Hello", "World", "Templates"};
    size_t strLen = sizeof(strArr) / sizeof(strArr[0]);

    std::cout << "strArr: ";
    iter(strArr, strLen, print<std::string>);
    std::cout << std::endl;

    float floatArr[] = {1.1f, 2.2f, 3.3f, 4.4f};
    size_t floatLen = sizeof(floatArr) / sizeof(floatArr[0]);

    std::cout << "floatArr: ";
    iter(floatArr, floatLen, print<float>);
    std::cout << std::endl;

    return 0;
}

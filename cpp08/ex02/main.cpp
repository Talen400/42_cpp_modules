#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main() {
    std::cout << "=== MutantStack ===" << std::endl;
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);
    std::cout << "top: " << mstack.top() << " (expected: 17)" << std::endl;
    mstack.pop();
    std::cout << "size after pop: " << mstack.size() << " (expected: 1)" << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;

    std::cout << "iterating: ";
    while (it != ite) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    std::cout << "top: " << mstack.top() << " (expected: 0)" << std::endl;

    std::stack<int> s(mstack);
    std::cout << "stack copy size: " << s.size() << " (expected: 5)" << std::endl;

    std::cout << "\n=== Using reverse iterators ===" << std::endl;
    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator rite = mstack.rend();
    std::cout << "reverse: ";
    while (rit != rite) {
        std::cout << *rit << " ";
        ++rit;
    }
    std::cout << std::endl;

    std::cout << "\n=== Const iterators ===" << std::endl;
    const MutantStack<int> cmstack(mstack);
    MutantStack<int>::const_iterator cit = cmstack.begin();
    MutantStack<int>::const_iterator cite = cmstack.end();
    std::cout << "const: ";
    while (cit != cite) {
        std::cout << *cit << " ";
        ++cit;
    }
    std::cout << std::endl;

    std::cout << "\n=== Comparing with std::list ===" << std::endl;
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(17);
    lst.pop_back();
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);

    std::cout << "list: ";
    for (std::list<int>::iterator lit = lst.begin(); lit != lst.end(); ++lit)
        std::cout << *lit << " ";
    std::cout << std::endl;

    std::cout << "\n=== Copy constructor MutantStack ===" << std::endl;
    MutantStack<int> copy(mstack);
    std::cout << "copy size: " << copy.size() << " (expected: 5)" << std::endl;
    copy.push(99);
    std::cout << "copy top: " << copy.top() << " (expected: 99)" << std::endl;
    std::cout << "original top: " << mstack.top() << " (expected: 0)" << std::endl;

    std::cout << "\n=== Assignment operator ===" << std::endl;
    MutantStack<int> assigned;
    assigned = mstack;
    std::cout << "assigned size: " << assigned.size() << " (expected: 5)" << std::endl;

    return 0;
}

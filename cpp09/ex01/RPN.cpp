#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <cstdlib>
#include <iostream>

bool RPN::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::applyOp(int a, int b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0)
            throw std::exception();
        return a / b;
    }
    throw std::exception();
}

int RPN::evaluate(const std::string& expr) {
    std::stack<int> s;
    std::istringstream iss(expr);
    std::string token;

    while (iss >> token) {
        if (isOperator(token)) {
            if (s.size() < 2) {
                std::cerr << "Error" << std::endl;
                return -1;
            }
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            try {
                s.push(applyOp(a, b, token));
            } catch (...) {
                std::cerr << "Error" << std::endl;
                return -1;
            }
        } else {
            char* end;
            int num = std::strtol(token.c_str(), &end, 10);
            if (*end != '\0' || num < 0 || num > 9 || token.length() != 1) {
                std::cerr << "Error" << std::endl;
                return -1;
            }
            s.push(num);
        }
    }

    if (s.size() != 1) {
        std::cerr << "Error" << std::endl;
        return -1;
    }

    return s.top();
}

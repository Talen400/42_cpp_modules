#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <iostream>
#include <stdexcept>

bool RPN::isOperator(const std::string& token) {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::applyOp(int a, int b, const std::string& op) {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") {
		if (b == 0)
			throw std::runtime_error("division by zero");
		return a / b;
	}
	throw std::runtime_error("unknown operator");
}

int RPN::evaluate(const std::string& expr) {
	std::stack<int> s;
	std::istringstream iss(expr);
	std::string token;

	while (iss >> token) {
		if (isOperator(token)) {
			if (s.size() < 2)
				throw std::runtime_error("insufficient operands");

			int b = s.top(); s.pop();
			int a = s.top(); s.pop();
			s.push(applyOp(a, b, token));
		} else {
			int num;
			std::istringstream tokstream(token);
			if (!(tokstream >> num) || num < 0 || num > 9 || token.length() != 1)
				throw std::runtime_error("invalid token");
			s.push(num);
		}
	}

	if (s.size() != 1)
		throw std::runtime_error("invalid expression");

	return s.top();
}

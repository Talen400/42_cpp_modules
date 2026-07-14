#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN {
	private:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		static bool isOperator(const std::string& token);
		static int applyOp(int a, int b, const std::string& op);

	public:
		static int evaluate(const std::string& expr);
};

#endif

#include <iostream>
#include <typeinfo>
#include <limits>
#include "ScalarConverter.hpp"
#include <string>

static void	separator(const std::string &label)
{
	std::ostream	&out = std::cout;
	out << "\n===" << label << "===\n" << std::endl;
}

int	main()
{
	separator("Form Canonic ScalarConverter test");
	{
		ScalarConverter	a;
		ScalarConverter	b(a);
		ScalarConverter	c = b;
	}
	char c;
	int *p1 = (int *) (&c);
	*p1 = 3;
	if (c == 3)
		std::cout << "Compiler ignore its" << std::endl;
	else
		std::cout << "The value was modified" << std::endl;
}


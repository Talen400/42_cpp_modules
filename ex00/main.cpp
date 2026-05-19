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
}

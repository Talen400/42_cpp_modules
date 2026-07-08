#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {};

ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void) other; };

ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &other)
{
	(void) other;
	return (*this);
};

ScalarConverter::~ScalarConverter() {}

static void	convert_char(double val)
{
	if (std::isnan(val) || std::isinf(val)
		|| val > std::numeric_limits<char>::max()
		|| val < std::numeric_limits<char>::min())
	{
		std::cout << "char: impossible" << '\n';
		return ;
	}
	char c = static_cast<char>(val);
	std::cout << "char: ";
	if (std::isprint(c))
		std::cout << "\'" << c << "\'" << std::endl;
	else
		std::cout << "Non displayable" << std::endl;
}

static void	convert_int(double val)
{
	if (std::isnan(val) || std::isinf(val)
		|| val > std::numeric_limits<int>::max()
		|| val < std::numeric_limits<int>::min())
	{
		std::cout << "int: impossible" << std::endl;
		return ;
	}
	std::cout << "int: " << static_cast<int>(val) << std::endl;
}

static void	convert_float(double val)
{
	std::cout << "float: ";
	if (std::isnan(val))
		std::cout << "nanf";
	else if (std::isinf(val))
		std::cout << (val > 0 ? "+inff" : "-inff");
	else
		std::cout << std::fixed << std::setprecision(1)
			<< static_cast<float>(val) << "f";
	std::cout << std::endl;
}

static void	convert_double(double val)
{
	std::cout << "double: ";
	if (std::isnan(val))
		std::cout << "nan";
	else if (std::isinf(val))
		std::cout << (val > 0 ? "+inf" : "-inf");
	else
		std::cout << std::fixed << std::setprecision(1) << val;
	std::cout << std::endl;
}

void	ScalarConverter::convert(const std::string &in)
{
	double value;
	char	*end;

	if (in == "nan" || in == "+inf" || in == "-inf" || in == "inf"
		|| in == "nanf" || in == "+inff" || in == "-inff" || in == "inff")
		value = strtod(in.c_str(), &end);
	else if(in.length() == 3 && in[0] == '\'' && in[2] == '\'')
		value = static_cast<double>(in[1]);
	else if (in.length() == 1 && !std::isdigit(in[0]))
		value = static_cast<double>(in[0]);
	else
	{
		value = strtod(in.c_str(), &end);
		if (*end != '\0' && !(*end == 'f' && *(end + 1) == '\0'))
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return ;
		}
	}
	convert_char(value);
	convert_int(value);
	convert_float(value);
	convert_double(value);
}



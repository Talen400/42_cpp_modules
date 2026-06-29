#include "Harl.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "example: ./harlFilter \"<warn text>\"" 
				  << std::endl;
		return (1);
	}

	std::string level;
	level = argv[1];

	Harl harl;
	harl.complain(level);
}

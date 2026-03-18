#include <iostream>

int	main(void)
{
	std::string brain = "HI THIS IS BRAIN";
	std::string* stringPTR = &brain;
	std::string& stringREF = brain;

	// memory
	std::cout << brain	<< std::endl;
	std::cout << *stringPTR << std::endl;
	std::cout << stringREF << std::endl;

	// adress
	std::cout << &brain	<< std::endl;
	std::cout << stringPTR << std::endl;
	std::cout << &stringREF << std::endl;
}

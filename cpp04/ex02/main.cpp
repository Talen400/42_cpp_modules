#include "helpers.h"

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

static void	separator(const std::string &label)
{
	std::cout << "\n=== " << label << " ===" << std::endl;
}

int	main(void)
{
	separator("Without Animal concrete");
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound();
		j->makeSound();
		delete i;
		delete j;
	}
}

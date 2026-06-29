#include "Cat.hpp"

Cat::Cat(): Animal()
{
	type = "Cat";
	label("Cat", type, "Constructor Default");
}

Cat::Cat(const Cat &other): Animal(other)
{
	type = "Cat";
	label("Cat", type, "Constructor Copy");
}

Cat	&Cat::operator=(const Cat &other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		type = "Cat";
	}
	label("Cat", type, "Constructor Copy Assignament");
	return (*this);
}

Cat::~Cat() {
	label("Cat", type, "Destructor");
}

std::string	Cat::getType() const
{
	return (type);
}

void	Cat::setType(const std::string &type)
{
	this->type = type;
}

void	Cat::makeSound() const
{
	std::cout << "MEOW MEOW!" << std::endl;
}

#include "Animal.hpp"

Animal::Animal(): type("Animal")
{
	label("Animal", type, "Constructor Default");
}

Animal::Animal(const Animal &other): type(other.type)
{
	label("Animal", type, "Constructor Copy");
}

Animal	&Animal::operator=(const Animal &other)
{
	if (this != &other)
		type = other.type;
	label("Animal", type, "Constructor Copy Assignament");
	return (*this);
}

Animal::~Animal() {
	label("Animal", type, "Destructor");
}

std::string	Animal::getType() const
{
	return (type);
}

void	Animal::setType(const std::string &type)
{
	this->type = type;
}

void	Animal::makeSound() const
{
	std::cout << "I am void animal" << std::endl;
}


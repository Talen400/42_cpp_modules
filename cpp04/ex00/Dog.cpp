#include "Dog.hpp"

Dog::Dog(): Animal()
{
	type = "Dog";
	label("Dog", type, "Constructor Default");
}

Dog::Dog(const Dog &other): Animal(other)
{
	type = "Dog";
	label("Dog", type, "Constructor Copy");
}

Dog	&Dog::operator=(const Dog &other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		type = "Dog";
	}
	label("Dog", type, "Constructor Copy Assignament");
	return (*this);
}

Dog::~Dog() {
	label("Dog", type, "Destructor");
}

std::string	Dog::getType() const
{
	return (type);
}

void	Dog::setType(const std::string &type)
{
	this->type = type;
}

void	Dog::makeSound() const
{
	std::cout << "AU AU!" << std::endl;
}

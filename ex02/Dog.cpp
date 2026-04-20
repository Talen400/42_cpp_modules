#include "Dog.hpp"

Dog::Dog(): Animal()
{
	type = "Dog";
	_brains = new Brain;
	label("Dog", type, "Constructor Default");
}

Dog::Dog(const Dog &other): Animal(other)
{
	type = "Dog";
	_brains = new Brain(*other._brains);
	label("Dog", type, "Constructor Copy");
}

Dog	&Dog::operator=(const Dog &other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		delete _brains;
		_brains = new Brain(*other._brains);
		type = "Dog";
	}
	label("Dog", type, "Constructor Copy Assignament");
	return (*this);
}

Dog::~Dog() {
	delete _brains;
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

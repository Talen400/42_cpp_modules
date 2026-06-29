#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(): type("Animal")
{
	label("WrongAnimal", type, "Constructor Default");
}

WrongAnimal::WrongAnimal(const WrongAnimal &other): type(other.type)
{
	label("WrongAnimal", type, "Constructor Copy");
}

WrongAnimal	&WrongAnimal::operator=(const WrongAnimal &other)
{
	if (this != &other)
		type = other.type;
	label("WrongAnimal", type, "Constructor Copy Assignament");
	return (*this);
}

WrongAnimal::~WrongAnimal() {
	label("WrongAnimal", type, "Destructor");
}

std::string	WrongAnimal::getType() const
{
	return (type);
}

void	WrongAnimal::setType(const std::string &type)
{
	this->type = type;
}

void	WrongAnimal::makeSound() const
{
	std::cout << "I am void animal" << std::endl;
}



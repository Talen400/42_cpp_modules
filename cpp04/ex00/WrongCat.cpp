#include "WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal()
{
	type = "WrongCat";
	label("WrongCat", type, "Constructor Default");
}

WrongCat::WrongCat(const WrongCat &other): WrongAnimal(other)
{
	type = "WrongCat";
	label("WrongCat", type, "Constructor Copy");
}

WrongCat	&WrongCat::operator=(const WrongCat &other)
{
	if (this != &other)
	{
		WrongAnimal::operator=(other);
		type = "WrongCat";
	}
	label("WrongCat", type, "Constructor Copy Assignament");
	return (*this);
}

WrongCat::~WrongCat() {
	label("WrongCat", type, "Destructor");
}

std::string	WrongCat::getType() const
{
	return (type);
}

void	WrongCat::setType(const std::string &type)
{
	this->type = type;
}

void	WrongCat::makeSound() const
{
	std::cout << "MEOW MEOW!" << std::endl;
}

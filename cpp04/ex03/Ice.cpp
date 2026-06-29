#include "Ice.hpp"

Ice::Ice(): AMateria("ice") {};
Ice::Ice(const Ice &other): AMateria(other) {}

Ice::~Ice()
{
	// text out
};

Ice	&Ice::operator=(const Ice &other)
{
	if (this != &other)
		AMateria::operator=(other);
	return *this;
}

Ice	*Ice::clone() const
{
	return (new Ice(*this));
};

void	Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " <<  target.getName() << " *" << std::endl;
}

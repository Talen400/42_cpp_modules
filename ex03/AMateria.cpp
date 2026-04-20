#include "amateria.h"

AMateria::AMateria(): _type("Ice") {}
AMateria::AMateria(const AMateria &other): _type(other._type) {}

AMateria	&AMateria::operator=(const AMateria &other)
{
	if (this != &other)
		_type = other._type;
	return (*this);
}

AMateria::~AMateria() {}
AMateria::AMateria(const std::string &type): _type(type) {}

std::string const	&AMateria::getType() const
{
	return (_type);
}


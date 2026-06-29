#include "AMateria.hpp"

AMateria::AMateria(): _type("Ice") {}
AMateria::AMateria(const AMateria &other): _type(other._type) {}

AMateria	&AMateria::operator=(const AMateria &other)
{
	(void ) other;
	return (*this);
}

AMateria::~AMateria() {}
AMateria::AMateria(const std::string &type): _type(type) {}

std::string const	&AMateria::getType() const
{
	return (_type);
}

void	AMateria::setType(const std::string &type)
{
	_type = type;
}

void	AMateria::use(ICharacter &target)
{
	(void ) target;
}


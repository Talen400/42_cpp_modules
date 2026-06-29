#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
};

MateriaSource::MateriaSource(const MateriaSource &other)
{
	for (int i = 0; i < 4; i++)	
		_inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : NULL;
};


MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
		delete _inventory[i];
};

MateriaSource	&MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
		for (int i = 0; i < 4; i++)	
		{
			delete _inventory[i];
			_inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : NULL;
		}
	}
	return (*this);
}

void	MateriaSource::learnMateria(AMateria *m)
{
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i] == NULL)
		{
			_inventory[i] = m;
			return ;
		}
	}
}

AMateria	*MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i] != NULL && _inventory[i]->getType() == type)
			return _inventory[i]->clone();
	}
	return NULL;
}

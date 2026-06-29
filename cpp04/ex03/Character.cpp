#include "Character.hpp"

Character::Character(): _name("no_name") 
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
}
Character::Character(const Character &other): _name(other._name) 
{

	for (int i = 0; i < 4; i++)
		_inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : NULL;
}

Character	&Character::operator=(const Character &other)
{
	if (this != &other)
	{
		_name = other._name;
		for (int i = 0; i < 4; i++)
		{
			delete _inventory[i];
			_inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : NULL;
		}
	}
	return (*this);
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
		delete _inventory[i];
	// text out
};

Character::Character(const std::string &name): _name(name)
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
}

const std::string	&Character::getName() const
{
	return (_name);
}

void	Character::equip(AMateria *m)
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

void	Character::unequip(int idx)
{
	if (idx >= 0 && idx < 4)
		_inventory[idx] = NULL;
}

void	Character::use(int idx, ICharacter &target)
{
	if (idx >= 0 && idx < 4 && _inventory[idx] != NULL)
		_inventory[idx]->use(target);
}

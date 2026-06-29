#include "ClapTrap.hpp"

ClapTrap::ClapTrap() 
{
	_name = "Default";
	_hitPoint = 10;
	_energyPoint = 10;
	_attackDamage = 0;
	std::cout << "ClapTrap '" << _name << "' is clap!" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
{
	_name = name;
	_hitPoint = 10;
	_energyPoint = 10;
	_attackDamage = 0;
	std::cout << "Claptrap '" << _name << "' is clap!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	_name = other._name;
	_hitPoint = other._hitPoint;
	_energyPoint = other._energyPoint;
	_attackDamage = other._attackDamage;
	std::cout << "Claptrap '" << _name << "' is clap from other!" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	if (this != &other) {
		_name = other._name;
		_hitPoint = other._hitPoint;
		_energyPoint = other._energyPoint;
		_attackDamage = other._attackDamage;
	}
	std::cout << "ClapTrap '" << _name << "' is clapted!" << std::endl;
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Claptrap '" << _name << "' is trapped :<" << std::endl;
}

void	ClapTrap::attack(const std::string &target)
{
	if (_hitPoint == 0)
	{
		std::cout << "ClapTrap '" << _name << "' is dead and can't attack!" << std::endl;
		return ;
	}
	if (_energyPoint == 0)
	{
		std::cout << "ClapTrap '" << _name << "' is without energy!" << std::endl;
		return ;
	}
	_energyPoint--;
	std::cout << "Claptrap '"
			 << _name << "' attacks '"
			 << target << "', causing "
			 << _attackDamage << " points of damage"
			 << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoint == 0)
	{
		std::cout << "ClapTrap '" << _name << "' is dead and can't attack!" << std::endl;
		return ;
	}
	if (amount >= _hitPoint)
		_hitPoint = 0;
	else
		_hitPoint -= amount;

	std::cout << "ClapTrap '" << _name << "' lost " << amount << " of points life !" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoint == 0)
	{
		std::cout << "ClapTrap '" << _name << "' is dead and can't attack!" << std::endl;
		return ;
	}
	if (_energyPoint == 0)
	{
		std::cout << "ClapTrap '" << _name << "' is without energy!" << std::endl;
		return ;
	}
	_hitPoint += amount;
	_energyPoint -= 1;

	std::cout << "ClapTrap '" << _name << "' repaired with " << amount << std::endl;
}

void	ClapTrap::printStatus() const
{
	std::cout << _name << " status:" << std::endl
			  << "hitPoints: " << _hitPoint << std::endl
			  << "energyPoints: " << _energyPoint << std::endl
			  << "attackDamage: " << _attackDamage << std::endl;
}

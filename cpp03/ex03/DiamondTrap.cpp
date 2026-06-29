#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(): ClapTrap(),
	ScavTrap(), FragTrap(), _name("Default")
{
	_hitPoint = 100;
	_energyPoint = 50;
	_attackDamage = 30;
	
	std::cout << "DiamondTrap '" << _name << "' is diamond!" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name): ClapTrap(name + "_clap_name"),
	ScavTrap(name), FragTrap(name), _name(name)
{
	_hitPoint = 100;
	_energyPoint = 50;
	_attackDamage = 30;
	
	std::cout << "DiamondTrap '" << _name << "' is diamond!" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other): ClapTrap(other),
	ScavTrap(other), FragTrap(other), _name(other._name)
{
	std::cout << "DiamondTrap '" << _name << "' is diamond from other!" << std::endl;
}

DiamondTrap	&DiamondTrap::operator=(const DiamondTrap &other)
{
	if (this != &other)
	{
		ClapTrap::operator=(other);
		_name = other._name;
	}
	std::cout << "DiamondTrap '" << _name << "' is diamond from other!" << std::endl;
	return *this;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "Diamondtrap '" << _name << "' is trapped :<" << std::endl;
}

void	DiamondTrap::whoAmI()
{
	std::cout << "I am " << _name << " and my ClapTrap name is " << ClapTrap::_name << std::endl;
}

void	DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

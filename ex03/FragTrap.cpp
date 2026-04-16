#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap()
{
	_hitPoint = 100;
	_energyPoint = 100;
	_attackDamage = 30;
	_highFive = false;

std::cout << "FragTrap '" << _name << "' is frag!" << std::endl;
}

FragTrap::FragTrap(const std::string &name): ClapTrap(name)
{
	_hitPoint = 100;
	_energyPoint = 100;
	_attackDamage = 30;
	_highFive = false;

	std::cout << "FragTrap '" << _name << "' is frag!" << std::endl;
}

FragTrap::FragTrap(const FragTrap &other): ClapTrap(other)
{
	_highFive = other._highFive;
	std::cout << "FragTrap '" << _name << "' is frag from other!" << std::endl;
}

FragTrap	&FragTrap::operator=(const FragTrap &other)
{
	if (this != &other)
	{
		ClapTrap::operator=(other);
		_highFive = other._highFive;
	}
	std::cout << "FragTrap '" << _name << "' is frag from other!" << std::endl;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "Fragtrap '" << _name << "' is trapped :<" << std::endl;
}

void	FragTrap::attack(const std::string &target)
{
	if (_hitPoint == 0)
	{
		std::cout << "FragTrap '" << _name << "' is dead and can't attack!" << std::endl;
		return ;
	}
	if (_energyPoint == 0)
	{
		std::cout << "FragTrap '" << _name << "' is without energy!" << std::endl;
		return ;
	}
	_energyPoint--;
	std::cout << "FragTrap '"
			 << _name << "' attacks '"
			 << target << "', causing "
			 << _attackDamage << " points of damage"
			 << std::endl;
}

void	FragTrap::highFivesGuy()
{
	if (_highFive)
	{
		std::cout << _name + " High Five, Guys!" << std::endl;
		_highFive = false;
	}
	else
	{
		std::cout << _name + " no High Five, Guys :<" << std::endl;
		_highFive = true;
	}
}

void	FragTrap::printStatus() const
{
	std::cout << "FragTrap " << _name << " status:" << std::endl
			  << "hitPoints: " << _hitPoint << std::endl
			  << "energyPoints: " << _energyPoint << std::endl
			  << "attackDamage: " << _attackDamage << std::endl
			  << "HighFive: " << ((_highFive) ? "True" : "False") << std::endl;
}

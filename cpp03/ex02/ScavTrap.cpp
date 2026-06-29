#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
	_hitPoint = 100;
	_energyPoint = 50;
	_attackDamage = 20;
	_guard = false;

	std::cout << "ScavTrap '" << _name << "' is scav!" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name): ClapTrap(name)
{	
	_hitPoint = 100;
	_energyPoint = 50;
	_attackDamage = 20;
	_guard = false;
	std::cout << "ScavTrap '" << _name << "' is scav!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other): ClapTrap(other)
{
	_guard = other._guard;
	std::cout << "ScavTrap '" << _name << "' is scav from other!" << std::endl;
}

ScavTrap	&ScavTrap::operator=(const ScavTrap &other)
{
	if (this != &other)
	{
		ClapTrap::operator=(other);
		_guard = other._guard;
	}
	std::cout << "ScavTrap '" << _name << "' is scav from other!" << std::endl;
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "Scavtrap '" << _name << "' is trapped :<" << std::endl;
}


void	ScavTrap::attack(const std::string &target)
{
	if (_hitPoint == 0)
	{
		std::cout << "ScavTrap '" << _name << "' is dead and can't attack!" << std::endl;
		return ;
	}
	if (_energyPoint == 0)
	{
		std::cout << "ScavTrap '" << _name << "' is without energy!" << std::endl;
		return ;
	}
	_energyPoint--;
	std::cout << "ScavTrap '"
			 << _name << "' attacks '"
			 << target << "', causing "
			 << _attackDamage << " points of damage"
			 << std::endl;
}

void	ScavTrap::guardGate()
{
	if (_guard)
	{
		std::cout << _name + " has out Gate mode!" << std::endl;
		_guard = false;
	}
	else
	{
		std::cout << _name + " has entered Gate mode!" << std::endl;
		_guard = true;
	}
}

void	ScavTrap::printStatus() const
{

	std::cout << "ScavTrap " << _name << " status:" << std::endl
			  << "hitPoints: " << _hitPoint << std::endl
			  << "energyPoints: " << _energyPoint << std::endl
			  << "attackDamage: " << _attackDamage << std::endl
			  << "guard: " << ((_guard) ? "True" : "False") << std::endl;
}

#include "ClapTrap.hpp"
#include <iostream>

void	separator(const std::string &label)
{
	std::cout << std::endl << "==" << label << "==" << std::endl;
}

int	main(void) 
{

	separator("TEST 1: Constructors and destructor messages");
	{
		ClapTrap def;                      // default constructor
		ClapTrap named("Claptrap-9000");   // name constructor
		ClapTrap copy(named);              // copy constructor
		ClapTrap assigned = def;           // copy assignment
	}
 
	separator("TEST 2: Normal attack");
	{
		ClapTrap ct("Turret");
		ct.printStatus();
		ct.attack("Bandit");
		ct.printStatus();
	}
 
	separator("TEST 3: takeDamage and beRepaired");
	{
		ClapTrap ct("Loader");
		ct.takeDamage(3);
		ct.printStatus();
		ct.beRepaired(2);
		ct.printStatus();
	}
 
	separator("TEST 4: Attack drains energy — ClapTrap stops at 0");
	{
		ClapTrap ct("BotA");
		for (int i = 0; i < 11; i++)
			ct.attack("Target");
		ct.printStatus();
	}
 
	separator("TEST 5: Dead ClapTrap cannot act");
	{
		ClapTrap ct("Fragged");
		ct.takeDamage(10);
		ct.printStatus();
		ct.attack("Ghost");
		ct.beRepaired(5);
		ct.printStatus();
	}
 
	separator("TEST 6: takeDamage more than current hp");
	{
		ClapTrap ct("Fragile");
		ct.takeDamage(999);
		ct.printStatus();
	}
 
	separator("TEST 7: Repair when out of energy");
	{
		ClapTrap ct("Drained");
		for (int i = 0; i < 10; i++)
			ct.attack("Dummy");
		ct.beRepaired(5);
		ct.printStatus();
	}

	separator("TEST 8: Attack damage of 0 (default)");
	{
		ClapTrap ct("Pacifist");
		ct.attack("Wall");
		ct.printStatus();
	}
 
	return 0;

}


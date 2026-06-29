#include "ScavTrap.hpp"
#include "FragTrap.hpp"

#include <iostream>

int	main(void)
{
	{
		ScavTrap a;
		ScavTrap b(a);
		ScavTrap c;
	
		c = b;

		c.printStatus();
	}
	std::cout << std::endl;
	{
		FragTrap a;
		FragTrap b(a);
		FragTrap c;

		c = b;

		c.printStatus();
	}
	return (0);
}

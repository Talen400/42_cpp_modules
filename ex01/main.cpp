#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	ScavTrap a;
	ScavTrap b(a);
	ScavTrap c;
	
	c = b;

	c.printStatus();
	return (1);
}

#include "DiamondTrap.hpp"

#include <iostream>

int	main(void)
{
	{
		DiamondTrap a;
		DiamondTrap b(a);
		DiamondTrap c;

		c = b;

		c.attack("bah");
		c.whoAmI();
	}

	return (0);
}

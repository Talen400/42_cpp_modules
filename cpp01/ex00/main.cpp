#include "Zombie.h"

int	main(void)
{
	/*
	 * Allocating in Stack
	 *
	 * Note the compiler will destroy (deallocate)
	 * in end of program
	 */

	Zombie maria;

	maria.announce();

	Zombie maria_without_name("maria_without_name");

	maria_without_name.announce();

	/*
	 * Allocating with new (malloc in background)
	 * And delete (deallocate)
	 *
	 */

	Zombie *joao = newZombie("joan");
	joao->announce();
	delete joao;

	/*
	 * randomChump create a object in stack
	 * But the object is only into in function
	 * where declared
	 *
	 */

	randomChump("bob");
	return (0);
}

#include "Zombie.h"

int	main(void)
{
	/*
	 * Allocation with new []
	 *
	 * In delete, compiler does two things:
	 *
	 * First, it clears the memory of each object.
	 * And then, it clears the entire memory.
	 *
	 */

	int	N;

	N = 10;
	Zombie *horde = zombieHorde(N, "john");
	for (int i = 0; i < N; i++)
		horde[i].announce();
	delete[] horde;
	return (0);
}

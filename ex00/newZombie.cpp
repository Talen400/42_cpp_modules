#include "Zombie.h"

Zombie	*newZombie(std::string name){
	Zombie *newZombie = new Zombie(name);
	return (newZombie);
}

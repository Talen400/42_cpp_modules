#include "Zombie.hpp"

Zombie::Zombie(){}

Zombie::Zombie(const std::string &name)
{
	_name = name;
}

Zombie::~Zombie()
{
	std::cout << _name << ": ARRRGGG!!!" << std::endl;
}

void	Zombie::announce(void){
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string &name)
{
	this->_name = name;
}

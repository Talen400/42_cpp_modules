#include "HumanB.hpp"

HumanB::HumanB(const std::string name) {
	_name = name;
}

HumanB::~HumanB() {}

void	HumanB::setWeapon(Weapon &weapon){
	_weapon = &weapon;
}

void	HumanB::setType(const std::string type){
	_weapon->setType(type);
}

void	HumanB::attack()
{
	std::cout << _name << " attacks with their "
				<< _weapon->getType()
				<< std::endl;
}


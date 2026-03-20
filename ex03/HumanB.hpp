#ifndef	HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
	private:
		Weapon*		_weapon;
		std::string	_name;

	public:
		HumanB(const std::string name);
		~HumanB();
		void setWeapon(Weapon &weapon);
		void setType(const std::string type);
		void attack();
};

#endif

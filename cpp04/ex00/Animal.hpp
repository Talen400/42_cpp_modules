#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include "helpers.h"

class Animal
{
	protected:
		std::string	type;
	
	public:
		Animal();
		Animal(const Animal &other);
		Animal	&operator=(const Animal &other);
		virtual ~Animal();

		std::string	getType() const;
		void		setType(const std::string &type);

		virtual void	makeSound() const;
};

#endif

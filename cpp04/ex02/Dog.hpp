#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog: public Animal
{
	private:
		Brain *_brains;

	public:
		Dog();
		Dog(const Dog &other);
		Dog	&operator=(const Dog &other);
		~Dog();

		std::string	getType() const;
		void		setType(const std::string &type);

		void	makeSound() const;
};

#endif

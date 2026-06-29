#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include "helpers.h"

class WrongAnimal
{
	protected:
		std::string	type;
	
	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal &other);
		WrongAnimal	&operator=(const WrongAnimal &other);
		virtual ~WrongAnimal();

		std::string	getType() const;
		void		setType(const std::string &type);

		void	makeSound() const;
};

#endif

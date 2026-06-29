#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat: public Animal
{
	private:
		Brain *_brains;

	public:
		Cat();
		Cat(const Cat &other);
		Cat	&operator=(const Cat &other);
		~Cat();

		std::string	getType() const;
		void		setType(const std::string &type);

		void		makeSound() const;
};

#endif

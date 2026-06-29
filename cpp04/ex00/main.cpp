#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

static void	separator(const std::string &label)
{
	std::cout << "\n=== " << label << " ===" << std::endl;
}

int	main(void)
{
	separator("Animal - Orthodox Canonical Form");
	{
		Animal	a;
		Animal	b(a);
		Animal	c;

		c = b;
		c.makeSound();
		std::cout << (&a == &b ? "SAME" : "DIFFERENT objects") << std::endl;
	}
	separator("Dog - Orthodox Canonical Form");
	std::cout << std::endl;
	{
		Dog	a;
		Dog	b(a);
		Dog	c;

		c = b;
		c.makeSound();
		std::cout << (&a == &b ? "SAME" : "DIFFERENT objects") << std::endl;
	}
	separator("Cat - Orthodox Canonical Form");
	std::cout << std::endl;
	{
		Cat	a;
		Cat	b(a);
		Cat	c;

		c = b;
		c.makeSound();
		std::cout << (&a == &b ? "SAME" : "DIFFERENT objects") << std::endl;
	}
	separator("Polymorphim via Animal pointer");
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound();
		j->makeSound();
		meta->makeSound();
		delete meta;
		delete i;
		delete j;
	}
	separator("WrongAnimal - no virtual (no polymorphism)");
	{
		const WrongAnimal* meta = new WrongAnimal();
		const WrongAnimal* i = new WrongCat();
		std::cout << i->getType() << " " << std::endl;
		i->makeSound();
		meta->makeSound();
		delete meta;
		delete i;
	}
	return (0);
}

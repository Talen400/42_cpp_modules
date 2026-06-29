#include "amateria.h"

int	main(void)
{
	/*
	 * Knowledge about materia
	 */
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());


	/*
	 * Character
	 */
	ICharacter* me = new Character("me");
	
	/*
	 * Creating materia and equip to Character
	 */
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	/*
	 * Character using the materia in other Character
	 */
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;
	return 0;
}

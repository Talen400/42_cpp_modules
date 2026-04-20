#ifndef AMATERIA_HPP
# define AMATERIA_HPP

#include "amateria.h"

class AMateria
{
	protected:
		std::string	_type;
	
	public:
		AMateria();
		AMateria(const AMateria &other);
		AMateria &operator=(const AMateria &other);
		~AMateria();

		AMateria(const std::string &type);

		// Returns the materia type
		std::string const &getType() const;
		void	setType(const std::string &type);

		virtual AMateria *clone() const = 0;
		virtual void	use(ICharacter &target);
};

#endif

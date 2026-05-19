#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"

/*
 *
 * Factory Design Pattern
 * 
 * Consist: class CREATOR (Example: Intern in this code)
 * this class have functions CREATORS to create products, without know the
 * rules and constructions of derivates class (Robotomy, Presidential...)
 *
 */

class Intern
{
	public:
		Intern();
		Intern(const Intern &other);
		Intern	&operator=(const Intern &other);
		~Intern();

		AForm	*makeForm(std::string formName, std::string target);
};

struct	FormEntry
{
	std::string name;
	AForm	*(*create)(std::string target);
};

#endif

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {};
Intern::Intern(const Intern &other) { (void) other;};
Intern &Intern::operator=(const Intern &other)
{
	(void) other;
	return *this;
};

Intern::~Intern() {};

AForm	*createShrubberyCreationForm(std::string target)
{
	return new ShrubberyCreationForm(target);
};

AForm	*createPresidentialPardonForm(std::string target)
{
	return new PresidentialPardonForm(target);
};

AForm	*createRobotomyRequestForm(std::string target)
{
	return new RobotomyRequestForm(target);
};

AForm	*Intern::makeForm(std::string formName, std::string target)
{
	FormEntry	forms[] =
	{
		{"ShrubberyCreationForm", &createShrubberyCreationForm},
		{"RobotomyRequestForm", &createRobotomyRequestForm},
		{"PresidentialPardonForm", &createPresidentialPardonForm}
	};
	
	for (int i = 0; i < 3; i++)
	{
		if (forms[i].name == formName)
		{
			std::cout << "Intern cria " << formName << std::endl;
			return forms[i].create(target);
		}
	}
	std::cerr << "Intern: formulário desconhecido: " << formName << std::endl;
	throw AForm::FormInvalid();
};

#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm():
	AForm(),
	_target("null")
{};

PresidentialPardonForm::PresidentialPardonForm(const std::string target):
	AForm("PresidentialPardonForm", 25, 5),
	_target(target)
{};

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other):
	AForm(other),
	_target(other._target)
{};

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {};

std::string	PresidentialPardonForm::getTarget() const {return (_target); };

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	AForm::checkExecution(executor);
	std::cout << _target << " foi perdoado por Zaphod Beeblebrox" << std::endl;
}

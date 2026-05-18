#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm():
	AForm(),
	_target("null")
{};

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target):
	AForm(),
	_target(target)
{};

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other):
	AForm(other),
	_target(other._target)
{};

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) 
{
	if (this == &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
};

ShrubberyCreationForm::~ShrubberyCreationForm() {};

std::string	ShrubberyCreationForm::getTarget() { return (_target); };

void		ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (executor.getGrade() > getMinGradeExec())
		throw GradeTooLowException();
	if (!getSign())
		throw FormHasNotSigned();
	std::string	file_name;
	std::ofstream	file();
}


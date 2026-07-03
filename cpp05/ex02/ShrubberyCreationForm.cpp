#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm():
	AForm(),
	_target("null")
{};

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target):
	AForm("ShrubberyCreationForm", 25, 5),
	_target(target)
{};

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other):
	AForm(other),
	_target(other._target)
{};

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) 
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
};

ShrubberyCreationForm::~ShrubberyCreationForm() {};

std::string	ShrubberyCreationForm::getTarget() const { return (_target); };

void		ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	AForm::checkExecution(executor);

	std::ofstream ofs((_target + "_shrubbery").c_str());

	if (!ofs.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return ;
	}
	ofs << "this is a tree: (tree)" << std::endl;
	ofs.close();
}


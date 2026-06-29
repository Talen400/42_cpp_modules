#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm():
	AForm(),
	_target("null")
{};

RobotomyRequestForm::RobotomyRequestForm(const std::string target):
	AForm("RobotomyRequestForm", 72, 45),
	_target(target)
{};

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other):
	AForm(other),
	_target(other._target)
{};

RobotomyRequestForm	&RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {};

std::string	RobotomyRequestForm::getTarget() const {return (_target); };

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	AForm::checkExecution(executor);
	std::cout << "* sons da picareta do minecraft *" << std::endl;
	if (rand() % 2 == 0)
		std::cout << _target << " foi robotomizado com sucesso" << std::endl;
	else
		std::cout << _target << " falhou na robotomização" << std::endl;
}

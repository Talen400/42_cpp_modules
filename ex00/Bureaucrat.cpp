#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): _name("root"), _grade(1)
{
	std::cout << "Bureaucrat '" << _name << "' Construction Default" << std::endl;
};

Bureaucrat::Bureaucrat(const std::string &name, int grade): _name(name), _grade(grade)
{
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
	std::cout << "Bureaucrat '" << _name << "' Construction parameter" << std::endl;
};

Bureaucrat::Bureaucrat(const Bureaucrat &other): _grade(other._grade)
{
	std::cout << "Bureaucrat '" << _name << "' Construction from other Bureaucrat" << std::endl;
};

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
	{
		_grade = other._grade;
	}
	std::cout << "Bureaucrat '" << _name << "' Copy assignament" << std::endl;
	return *this;
};

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat '" << _name << "' Destruction" << std::endl;
};

std::string	Bureaucrat::getName() const
{
	return _name;
}

int	Bureaucrat::getGrade() const
{
	return _grade;
}

void	Bureaucrat::downGrade()
{
	if (_grade >= 150)
		throw GradeTooLowException();
	_grade++;
}

void	Bureaucrat::upGrade()
{
	if (_grade <= 1)
		throw GradeTooHighException();
	_grade--;
}

const char	*Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char	*Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

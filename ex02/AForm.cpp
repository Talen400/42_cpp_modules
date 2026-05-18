#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(): _name("root"), _min_grade(1), _min_grade_exec(1) {};

AForm::AForm(const std::string &name, int min_grade, int min_grade_exec):
	_name(name), _min_grade(min_grade), _min_grade_exec(min_grade_exec), _sign(false)
{};

AForm::AForm(const AForm &other):
	_name(other._name), _min_grade(other._min_grade),
	_min_grade_exec(other._min_grade_exec), _sign(false)
{};

AForm	&AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		_min_grade = other._min_grade;
		_min_grade_exec = other._min_grade_exec;
		_sign = false;
	}
	return (*this);
}

AForm::~AForm()
{

}

const char	*AForm::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}

const char	*AForm::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char	*AForm::FormHasSigned::what() const throw()
{
	return ("Form has signed!");
}

const char	*AForm::FormHasNotSigned::what() const throw()
{
	return ("Form has not signed!");
}

std::string	AForm::getName() const
{
	return (_name);
}

int			AForm::getMinGrade() const
{
	return (_min_grade);
}

int			AForm::getMinGradeExec() const
{
	return (_min_grade_exec);
}

bool		AForm::getSign() const
{
	return (_sign);
}

void		AForm::beSigned(Bureaucrat const &b)
{
	if (b.getGrade() > _min_grade)
		throw GradeTooLowException();
	if (_sign)
		throw FormHasSigned();
	_sign = true;
}

std::ostream	&operator<<(std::ostream &out, const AForm &b)
{
	out << "Info Form '" << b.getName() << "' :" << std::endl
		<< "min_grade: " << b.getMinGrade() << std::endl
		<< "min_grade_exec: " << b.getMinGradeExec() << std::endl
		<< "sign: " << (b.getSign() ? "TRUE" : "FALSE")
		<< std::endl;
	return out;
}

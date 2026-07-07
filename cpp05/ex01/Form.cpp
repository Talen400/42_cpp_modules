#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(): _name("root"), _min_grade(1), _min_grade_exec(1), _sign(false)
{
	std::cout << "Form '" << _name << "' construction default" << std::endl;
};

Form::Form(const std::string &name, int min_grade, int min_grade_exec):
	_name(name), _min_grade(min_grade), _min_grade_exec(min_grade_exec), _sign(false)
{
	if (min_grade < 1)
		throw GradeTooHighException();
	if (min_grade > 150)
		throw GradeTooLowException();
	std::cout << "Form '" << _name << "' Construction parameter" << std::endl;	
};

Form::Form(const Form &other):
	_name(other._name), _min_grade(other._min_grade), _min_grade_exec(other._min_grade_exec)
			,_sign(false)
{
	std::cout << "Form '" << _name << "' Construction from other Form" << std::endl;
}

Form	&Form::operator=(const Form &other)
{
	if (this != &other)
	{
		_sign = false;
	}
	std::cout << "Form '" << _name << "' Construction from other Bureaucrat" << std::endl;
	return (*this);
};

Form::~Form()
{
	std::cout << "Form '" << _name << "' Destruction" << std::endl;
};

std::string	Form::getName() const {	return (_name);}
int			Form::getMinGrade() const { return (_min_grade);}
int			Form::getMinGradeExec() const { return (_min_grade_exec);}
bool		Form::getSign() const { return (_sign);}

const char	*Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char	*Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

void	Form::beSigned(Bureaucrat &other)
{
	if (other.getGrade() > _min_grade)
		throw GradeTooLowException();
	_sign = true;
}

std::ostream	&operator<<(std::ostream &out, const Form &b)
{
	out << "Info Form '" << b.getName() << "' :" << std::endl
		<< "min_grade: " << b.getMinGrade() << std::endl
		<< "min_grade_exec: " << b.getMinGradeExec() << std::endl
		<< "sign: " << (b.getSign() ? "TRUE" : "FALSE")
		<< std::endl;
	return out;
}


#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(): _name("root"), _min_grade(1), _min_grade_exec(1), _sign(false) {};

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

AForm::~AForm() {}

std::string	AForm::getName() const { return (_name); }

int			AForm::getMinGrade() const { return (_min_grade); }

int			AForm::getMinGradeExec() const { return (_min_grade_exec); }

bool		AForm::getSign() const { return (_sign); }

void		AForm::beSigned(Bureaucrat const &b)
{
	if (b.getGrade() > _min_grade)
		throw GradeTooLowException();
	if (_sign)
		throw FormHasSigned();
	_sign = true;
}

void		AForm::checkExecution(Bureaucrat const &executor) const
{
	if (!_sign)
		throw FormHasNotSigned();
	if (executor.getGrade() > _min_grade_exec)
		throw GradeTooLowException();
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

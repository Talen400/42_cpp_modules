#ifndef AFORM_HPP
# define AFORM_HPP

#include <iostream>

class Bureaucrat;

/*
 *	std::exception
  *		└── std::runtime_error
  *  		└── AFormException
  *      		├── GradeTooHighException
  *     		├── GradeTooLowException
  *      		├── FormHasSigned
  *      		├── FormHasNotSigned
  *      		└── FormInvalid
  *
 */

class AForm
{
	private:
		const std::string	_name;
		int					_min_grade;
		int					_min_grade_exec;
		bool				_sign;

	protected:
		void	checkExecution(Bureaucrat const &executor) const;

	public:
		AForm();
		AForm(const std::string &name, int min_grade, int min_grade_exec);
		AForm(const AForm &other);
		AForm	&operator=(const AForm &other);

		virtual ~AForm();

		// class Father from std::exception::runtime_error
		
		class AFormException: public std::runtime_error
		{
			public:
				AFormException(const std::string &msg): std::runtime_error(msg) {}
		};

		// All class form AFormException
		
		// subject
		class GradeTooHighException: public AFormException
		{
			public:
				GradeTooHighException(): AFormException("Grade too high!") {}
		};
		class GradeTooLowException: public AFormException
		{
			public:
				GradeTooLowException(): AFormException("Grade too low!") {}
		};

		// Some helpers:
		class FormHasSigned: public AFormException
		{
			public:
				FormHasSigned(): AFormException("Form already signed!") {}
		};
		class FormHasNotSigned: public AFormException
		{
			public:
				FormHasNotSigned(): AFormException("Form not signed!") {}
		};

		// to Intern helper

		class FormInvalid: public AFormException
		{
			public:
				FormInvalid(): AFormException("Invalid Form") {}
		};

		std::string	getName() const;
		int			getMinGrade() const;
		int			getMinGradeExec() const;
		bool		getSign() const;

		virtual void	execute(Bureaucrat const &executor) const = 0;

		void beSigned(Bureaucrat const &b);
};

std::ostream	&operator<<(std::ostream &out, const AForm &f);

#endif

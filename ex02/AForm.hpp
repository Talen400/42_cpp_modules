#ifndef AFORM_HPP
# define AFORM_HPP

#include <iostream>

class Bureaucrat;

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

		~AForm();

		class GradeTooHighException: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class GradeTooLowException: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class FormHasSigned: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class FormHasNotSigned: public std::exception
		{
			public:
				virtual const char *what() const throw();
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

#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>

class Bureaucrat;

class Form
{
	private:
		const std::string	_name;
		int		_min_grade;
		int		_min_grade_exec;
		bool	_sign;

	public:
		Form();
		Form(const std::string &name, int min_grade, int min_grade_exec);
		Form(const Form &other);
		Form	&operator=(const Form &other);

		~Form();

		class GradeTooHighException: public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		
		class GradeTooLowException: public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		std::string	getName() const;
		int			getMinGrade() const;
		int			getMinGradeExec() const;
		bool		getSign() const;

		void		beSigned(Bureaucrat &other);
};

std::ostream	&operator<<(std::ostream &out, const Form &b);

#endif

#include "Bureaucrat.hpp"

int	main(void)
{
	{
		Bureaucrat _v;
		Bureaucrat a("test", 150);
		Bureaucrat b(a);
		Bureaucrat c = b;

		std::cout << b;
	}
	{
		try
		{
			Bureaucrat b("teste", 0);
		}
		catch (Bureaucrat::GradeTooHighException &e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (Bureaucrat::GradeTooLowException &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	{
		try
		{
			Bureaucrat b("grade_150", 150);
			b.upGrade();
			std::cout << b;
		}
		catch (Bureaucrat::GradeTooHighException &e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (Bureaucrat::GradeTooLowException &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	{
		try
		{
			Bureaucrat b("grade_1", 1);
			b.upGrade();
		}
		catch (Bureaucrat::GradeTooHighException &e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (Bureaucrat::GradeTooLowException &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

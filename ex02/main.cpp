#include <iostream>
#include <fstream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

static void	separator(const std::string &label)
{
	std::cout << "\n=== " << label << " ===" << std::endl; 
}

int	main(void)
{
	srand(time(NULL));
	separator("TEST 1: bureaucrat invalid");

	try { Bureaucrat bad("bad", 0); }
	catch (std::exception &e) { std::cout << e.what() << std::endl; }

	separator("ShrubberyCreationForm test");
	{
		Bureaucrat low("low", 150);
		Bureaucrat high("high", 1);
		ShrubberyCreationForm s("home");

		low.signForm(s);
		high.signForm(s);
		low.executeForm(s);
		high.executeForm(s);
	}
	separator("RobotomyRequestForm test");
	{
		Bureaucrat b("boss", 1);
		RobotomyRequestForm r("Bender");

		b.signForm(r);
		for (int i = 0; i < 3; i++)
			b.executeForm(r);
	}
	separator("PresidentialPardonForm test");
	{
		Bureaucrat low("low", 150);
		Bureaucrat high("high", 1);
		PresidentialPardonForm p("Arthur");

		low.signForm(p);
		high.signForm(p);
		high.executeForm(p);
	}
}

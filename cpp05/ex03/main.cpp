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
#include "Intern.hpp"

static void	separator(const std::string &label)
{
	std::cout << "\n=== " << label << " ===" << std::endl; 
}

int	main(void)
{
	srand(time(NULL));
	separator("Test canonic form:");
	{
		Intern a;
		Intern b(a);
		Intern c = b;
	}

	// The factory Intern
	Intern intern;

	separator("Create ShrubberyCreationForm");
	try 
	{
		AForm *f = intern.makeForm("ShrubberyCreationForm", "home");
		Bureaucrat b("Alice", 137);
		b.signForm(*f);
		b.executeForm(*f);
		delete f;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	separator("Create RobotomyRequestForm");
	try 
	{
		AForm *f = intern.makeForm("RobotomyRequestForm", "robot");
		Bureaucrat b("Robertin", 40);
		b.signForm(*f);
		b.executeForm(*f);
		delete f;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	separator("Create PresidentialPardonForm");
	try 
	{
		AForm *f = intern.makeForm("PresidentialPardonForm", "Presidential");
		Bureaucrat b("Zaphod", 3);
		b.signForm(*f);
		b.executeForm(*f);
		delete f;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	separator("Create a Invalid Form");
	try 
	{
		AForm *f = intern.makeForm("bah", "bah");
		if (f)
			delete f;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

#include "Bureaucrat.hpp"
#include "Form.hpp"

void	separator(const std::string &text)
{
	std::cout << "==" << text << "==" << std::endl;
}

int	main(void)
{
	separator("Test form Canonic of the Form class");
	{
		Form a;
		Form b(a);
		Form c = b;

		Form cidade("cidade", 4, 6);

		std::cout << cidade;
	}
	separator("Test of Form methods");
	{
		Bureaucrat juiz("root", 11);
		Form	forms("processo", 10, 1);

		juiz.signForm(forms);


		Bureaucrat juiz_2("root", 1);
		Form	forms_2("processo2", 150, 1);

		juiz_2.signForm(forms_2);
	}
}

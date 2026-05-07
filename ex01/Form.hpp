#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>

class Form
{
	private:
		const std::string	_name;
		int		min_grade;
		int		max_grade;

	public:
		Form();
		Form(const std::string &name,);
		Form();
};

#endif

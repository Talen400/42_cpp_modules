#include "PhoneBook.hpp"
#include <iomanip>

PhoneBook::PhoneBook()
{
	_len = 0;
	_index = 0;
}

void PhoneBook::addContact(const Contact &contact)
{
	_list_contact[_index] = contact;
	_index = (_index + 1) % 8;
	if (_len < 8)
		_len++;
}

std::string	PhoneBook::_truncate(std::string str) const
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void PhoneBook::searchContact(int index) const
{
	if (index >=0 && index < _len)
		_list_contact[index].printContact();
	else
		std::cout << "Invalid Contact" << std::endl;
}

void PhoneBook::displayList() const
{
	std::cout << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "last Name"  << "|" 
			  << std::setw(10) << "Nickname" << std::endl;

	for (int i = 0; i < _len; i++)
	{
		std::cout << std::setw(10) << i << "|" 
				  << std::setw(10) << _truncate(_list_contact[i].getFirstName()) << "|"
				  << std::setw(10) << _truncate(_list_contact[i].getLastName()) << "|"
				  << std::setw(10) << _truncate(_list_contact[i].getNickname()) << "|"
				  << std::endl;			  
	}
}

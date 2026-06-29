#include "Contact.hpp"

void	Contact::setContact(
		std::string number,
		std::string nickname,
		std::string secret,
		std::string first_name,
		std::string last_name)
{
	_number = number;
	_nickname = nickname;
	_secret = secret;
	_first_name = first_name;
	_last_name = last_name;
}

void		Contact::printContact(void) const
{
	std::cout << "Number: " << _number << std::endl;
	std::cout << "Nickname: " << _nickname << std::endl;
	std::cout << "Secret: " << _secret << std::endl;
	std::cout << "First name: " << _first_name << std::endl;
	std::cout << "Last name: " << _last_name << std::endl;
}

std::string	Contact::getNumber(void) const
{
	return (_number);
}

std::string	Contact::getNickname(void) const
{
	return (_nickname);
}

std::string Contact::getSecret(void) const
{
	return (_secret);
}

std::string Contact::getFirstName(void) const
{
	return (_first_name);
}

std::string Contact::getLastName(void) const
{
	return (_last_name);
}

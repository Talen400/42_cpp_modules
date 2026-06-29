#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>

class Contact
{
	private:
		std::string _number;
		std::string _nickname;
		std::string _secret;
		std::string _first_name;
		std::string _last_name;
		
	public:
		void setContact(
				std::string number,
				std::string nickname,
				std::string secret,
				std::string first,
				std::string last);
		void		printContact(void) const;
		std::string	getNumber(void) const;
		std::string	getNickname(void) const;
		std::string	getSecret(void) const;
		std::string	getFirstName(void) const;
		std::string	getLastName(void) const;
};

#endif

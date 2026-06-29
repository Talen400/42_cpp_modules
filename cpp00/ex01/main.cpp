#include <iostream>
#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <cstdlib>

static std::string	readField(const std::string &prompt) {
	std::string	input;

	while (true) {
		std::cout << prompt;
		if (!std::getline(std::cin, input))
		{
			std::cout << "Exiting..." << std::endl;
			std::exit(0);
		}
		if (!input.empty())
			return input;
		std::cout << "Field cannot be empty. Try again :)" << std::endl;
	}
}

int	main(int argc, char *argv[])
{
	PhoneBook 	Phone;
	std::string command;

	while (true)
	{
		std::cout << "command: ";
		if (!std::getline(std::cin, command))
		{
			std::cout << "Exiting..." << std::endl;
			break ;
		}

		if (command == "ADD")
		{
			Contact contact;

			std::string	number;
			std::string	nickname;
			std::string	first_name;
			std::string last_name;
			std::string	secret;

			number = readField("Number: ");
			nickname = readField("Nickname: ");
			first_name = readField("First Name: ");
			last_name = readField("Last Name: ");
			secret = readField("Secret: ");

			contact.setContact(number, nickname, secret, first_name, last_name);
			Phone.addContact(contact);
		}
		else if (command == "SEARCH")
		{
			std::string	indexStr;
			int			idx;
	
			Phone.displayList();
			indexStr = readField("Index: ");
			idx = atoi(indexStr.c_str());
			Phone.searchContact(idx);
		}
		else if (command == "EXIT")
			break ;
		else
			std::cout << "Insert a command valid" << std::endl;
	}
	(void ) argc;
	(void ) argv;
	return (0);
}

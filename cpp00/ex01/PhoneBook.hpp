#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact 	_list_contact[8];
		int			_len;
		int			_index;
		std::string	_truncate(std::string str) const;

	public:
		PhoneBook();
		void	addContact(const Contact &contact);
		void	searchContact(int index) const;
		void	displayList() const;
};

#endif


#include "Harl.hpp"

Harl::Harl() {}

Harl::~Harl() {}

void Harl::debug() {
	std::cout << "Eu amo ter bacon extra para o meu hambúrguer"
			  << " 7XL-duplo-queijo-triplo-picles-ketchup-especial." 
			  << " Eu realmente amo!" << std::endl;
}

void Harl::info() {
	std::cout << "Eu não acredito que adicionar bacon extra custa mais dinheiro."
			  << " Vocês não colocaram bacon suficiente no meu hambúrguer!"
			  << " Se vocês tivessem colocado, eu não estaria pedindo por mais!"
			  << std::endl;
}

void Harl::warning() {
	std::cout << "Eu acho que mereço ter bacon extra de graça."
			  << "Eu venho aqui há anos,"
			  << " enquanto você começou a trabalhar aqui apenas"
			  << " no mês passado."
			  << std::endl;
}

void Harl::error() {
	std::cout << "Isto é inaceitável!"
			  << "Eu quero falar com o gerente agora."
			  << std::endl;
}

int Harl::getLevel(const std::string &level) {
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
			return i;
	}
	return (-1);
}

void Harl::complain(std::string level) {

	switch (getLevel(level))
	{
		case 0:
			std::cout << "[ DEBUG ]" << std::endl;
			this->debug();
			std::cout << std::endl;
			// falls through
		case 1:
			std::cout << "[ INFO ]" << std::endl;
			this->info();
			std::cout << std::endl;
			// falls through
		case 2:
			std::cout << "[ WARNING ]" << std::endl;
			this->warning();
			std::cout << std::endl;
			// falls through
		case 3:
			std::cout << "[ ERROR ]" << std::endl;
			this->error();
			std::cout << std::endl;
			break;
		default:
			std::cout << "[ Provavelmente reclamando sobre problemas insignificantes ]" << std::endl;
	}
}

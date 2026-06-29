#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
{
	_accountIndex = _nbAccounts;
	_nbAccounts++;

	_amount = initial_deposit;
	_totalAmount += initial_deposit;

	_nbDeposits = 0;

	_nbWithdrawals = 0;
	
	_displayTimestamp();

	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";"
			  << "amount:" << initial_deposit << ";"
			  << "created"
			  << std::endl;
}

Account::~Account(void) {
	_displayTimestamp();

	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";"
			  << "amount:" << _amount << ";"
			  << "closed"
			  << std::endl;
}

int	Account::getNbAccounts(void){
	return (_nbAccounts);
}

int	Account::getTotalAmount(void){
	return (_totalAmount);
}

int	Account::getNbDeposits(void){
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals(void){
	return (_totalNbWithdrawals);
}

void	Account::makeDeposit(int deposit) {
	_displayTimestamp();

	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";"
			  << "p_amount:" << _amount << ";"
			  << "deposit:" << deposit << ";";

	_totalNbDeposits++;
	_nbDeposits++;
	_totalAmount += deposit;
	_amount += deposit;

	std::cout << "amount:" << _amount << ";"
			  << "nb_deposits:" << _nbDeposits
			  << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal) {
	_displayTimestamp();

	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";"
			  << "p_amount:" << _amount << ";";
	if (withdrawal > _amount)
	{
		std::cout << "withdrawal:" << "refused"
				  << std::endl;
		return (false);
	}
	else
		std::cout << "withdrawal:" << withdrawal << ";";
	_amount -= withdrawal;
	_totalAmount -= withdrawal;
	_nbWithdrawals++;
	_totalNbWithdrawals++;

	std::cout << "amount:" << _amount << ";"
			  << "nb_withdrawals:" << _nbWithdrawals
			  << std::endl;
	return (true);
}

int		Account::checkAmount(void) const {
	return (_amount);
}

void	Account::displayStatus( void ) const {
	_displayTimestamp();

	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";"
			  << "amount:" << _amount << ";"
			  << "deposits:" << _nbDeposits << ";"
			  << "withdrawals:" << _nbWithdrawals
			  << std::endl;
}

void	Account::displayAccountsInfos(void){
	_displayTimestamp();

	std::cout << " ";
	std::cout << "accounts:" << _nbAccounts << ";"
			  << "total:" << _totalAmount << ";"
			  << "deposits:" << _totalNbDeposits << ";"
			  << "withdrawals:" << _totalNbWithdrawals
			  << std::endl;
}

// format: [YYMMDD_HHMMSS]

void	Account::_displayTimestamp(void){
	std::time_t now = std::time(NULL);
	std::tm *lt = std::localtime(&now);

	std::cout << "["
			  << lt->tm_year + 1900
			  << std::setfill('0')
			  << std::setw(2) << lt->tm_mon + 1
			  << std::setw(2) << lt->tm_mday
			  << "_"
			  << std::setw(2) << lt->tm_hour
			  << std::setw(2) << lt->tm_min
			  << std::setw(2) << lt->tm_sec
			  << "]";
}

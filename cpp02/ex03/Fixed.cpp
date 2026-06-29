#include "Fixed.hpp"

Fixed::Fixed() {
	_value = 0;
};

Fixed::Fixed(const Fixed &other) {
	*this = other;
}

Fixed::Fixed(int const value)  :
	_value(value * (1 << _frac)) {}

Fixed::Fixed(float const value) : 
	_value(roundf(value * (1 << _frac))) {}

Fixed &Fixed::operator=(const Fixed &other) {
	if (this != &other)
		_value = other.getRawBits();
	return (*this);
};

Fixed::~Fixed() {
};

/*
 * Setters and getters
 */

int	Fixed::getRawBits(void) const {
	return (_value);
}

void Fixed::setRawBits(int const raw) {
	_value = raw;
}

/*
 * Converters
 */

float Fixed::toFloat(void) const {
	return (static_cast<float> (_value) / (1 << _frac));
}

int	Fixed::toInt(void) const {
	return (static_cast<float> (_value >> _frac));
}

/*
 * bools operators
 */

bool	Fixed::operator>(const Fixed &other) const {
	return (_value > other._value);
}

bool	Fixed::operator<(const Fixed &other) const {
	return (_value < other._value);
}

bool	Fixed::operator>=(const Fixed &other) const {
	return (_value >= other._value);
}

bool	Fixed::operator<=(const Fixed &other) const {
	return (_value <= other._value);
}

bool	Fixed::operator==(const Fixed &other) const {
	return (_value == other._value);
}

bool	Fixed::operator!=(const Fixed &other) const {
	return (_value != other._value);
}

/*
 * Operators
 */

Fixed	Fixed::operator+(const Fixed &other) const {
	Fixed res;

	res.setRawBits(_value + other._value);
	return (res);
}

Fixed	Fixed::operator-(const Fixed &other) const {
	Fixed res;

	res.setRawBits(_value - other._value);
	return (res);
}

Fixed	Fixed::operator*(const Fixed &other) const {
	Fixed res;

	res.setRawBits((_value * other._value) >> _frac);
	return (res);
}

Fixed	Fixed::operator/(const Fixed &other) const {
	Fixed res;

	res.setRawBits((_value << _frac) / other._value);
	return (res);
}

/*
 * Pre- and pro- increment
 * Pre- and pro- decrement
 */

Fixed&	Fixed::operator++(void) {
	this->_value++;
	return *this;
}

Fixed	Fixed::operator++(int) {
	Fixed tmp(*this);
	
	this->_value++;
	return tmp;
}

Fixed&	Fixed::operator--(void) {
	this->_value--;
	return *this;
}

Fixed	Fixed::operator--(int) {
	Fixed tmp(*this);

	this->_value--;
	return tmp;
}

/*
 * min and max functions
 */

Fixed	&Fixed::min(Fixed &a, Fixed &b) {
	return (a < b) ? a : b;
}

const Fixed	&Fixed::min(const Fixed &a, const Fixed &b) {
	return (a < b) ? a : b;
}

Fixed	&Fixed::max(Fixed &a, Fixed &b) {
	return (a > b) ? a : b;
}

const Fixed	&Fixed::max(const Fixed &a, const Fixed &b) {
	return (a > b) ? a : b;
}

/*
 * I/O stream
 */

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
	os << fixed.toFloat();
	return (os);
}

#include "Point.hpp"

Point::Point(): _x(0), _y(0) {};

Point::Point(float const x, float const y): _x(x), _y(y){};

Point::Point(const Point &point): _x(point._x), _y(point._y) {}

Point	&Point::operator=(const Point &other) {
	(void ) other;
	return *this;
}

Point::~Point() {};

/*
 * getters
 */

const Fixed	&Point::getX() const {
	return _x;
}

const Fixed	&Point::getY() const {
	return _y;
}

/*
 * The operators
 */

Point	Point::operator+(const Point &other) const {
	return Point(_x.toFloat() + other._x.toFloat(), _y.toFloat() + other._y.toFloat());
}

Point	Point::operator-(const Point &other) const {
	return Point(_x.toFloat() - other._x.toFloat(), _y.toFloat() - other._y.toFloat());
}
/*
 * I/O stream
 */

std::ostream &operator<<(std::ostream &os, const Point &point) {
	os << "(" << point.getX() << ", " << point.getY() << ")";
	return os;
}

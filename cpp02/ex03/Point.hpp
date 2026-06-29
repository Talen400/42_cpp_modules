#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class Point
{
	private:
		Fixed const	_x;
		Fixed const	_y;
	
	public:
		Point();
		Point(float const x, float const y);
		Point(const Point &point);
		Point	&operator=(const Point &other);
		~Point();

		const Fixed	&getX() const;
		const Fixed	&getY() const;

		Point	operator+(const Point &other) const;
		Point	operator-(const Point &other) const;
};

std::ostream	&operator<<(std::ostream &os, const Point &point);
bool	bsp(Point const a, Point const b,
				Point const c, Point const point);
#endif

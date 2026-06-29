#include "Point.hpp"

/*
 *  d1 = (B - A) x (P - A)
 *  d2 = (C - B) x (P - B)
 *  d3 = (A - C) x (P - C)
 */

float	cross(Point a, Point b, Point p)
{
	Point AB = b - a;
	Point AP = p - a;
	return (AB.getX().toFloat() * AP.getY().toFloat()
			- AB.getY().toFloat() * AP.getX().toFloat());
}

bool	bsp(Point const a, Point const b,
				Point const c, Point const point) {
	float d1 = cross(a, b, point);
	float d2 = cross(b, c, point);
	float d3 = cross(c, a, point);

	if (d1 == 0 || d2 == 0 || d3 == 0)
		return false;

	bool minus = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool sum = (d1 > 0) || (d2 > 0) || (d3 > 0);
	return !(minus & sum);
}

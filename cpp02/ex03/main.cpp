#include <iostream>
#include "Point.hpp"

void	test(const std::string &name, Point a, Point b, Point c,
		Point p, bool expected) {
	bool result = bsp(a, b, c, p);
	std::string status = (result == expected) ? "PASS" : "FAIL";
	std::cout << "[" << status << "] " << "Point" << p << " " << name << std::endl;
}

int	main(void) {
	Point point;

	std::cout << point << std::endl;

	Point point_with_numbers(5, 6);

	std::cout << point_with_numbers << std::endl;

	Point A(0, 0);
	Point B(4, 0);
	Point C(0, 4);

	std::cout << "triangle:" << " A" << A << " B" << B << " C" << C << std::endl;

	test("center point",		A, B, C, Point(1, 1),   true);
	test("near center",			A, B, C, Point(0.5, 0.5), true);

	// outside
	test("far outside",			A, B, C, Point(5, 5),   false);
	test("outside negative",	A, B, C, Point(-1, -1), false);
	test("outside right",		A, B, C, Point(3, 3),   false);

    // on edge (should be false)
	test("on edge AB",			A, B, C, Point(2, 0),   false);
	test("on edge AC",			A, B, C, Point(0, 2),   false);
	test("on hypotenuse",		A, B, C, Point(2, 2),   false);

	// on vertex (should be false)
	test("on vertex A",			A, B, C, Point(0, 0),   false);
	test("on vertex B",			A, B, C, Point(4, 0),   false);
	test("on vertex C",			A, B, C, Point(0, 4),   false);
}

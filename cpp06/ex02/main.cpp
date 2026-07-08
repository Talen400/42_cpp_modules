#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base*	generate(void)
{
	int	r = rand() % 3;

	if (r == 0)
		return (new A);
	if (r == 1)
		return (new B);
	return (new C);
}

void	identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << '\n';
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << '\n';
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << '\n';
}

void	identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << '\n';
		return ;
	}
	catch (...) {}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << '\n';
		return ;
	}
	catch (...) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << '\n';
		return ;
	}
	catch (...) {}
}

int	main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < 5; i++)
	{
		Base*	p = generate();

		std::cout << "identify(*p): ";
		identify(p);

		std::cout << "identify(&p): ";
		identify(*p);

		std::cout << '\n';
		delete p;
	}

	return (0);
}

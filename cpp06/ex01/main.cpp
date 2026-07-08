#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <stdint.h>

int	main()
{
	Data		original;
	Data		*deserialized;
	uintptr_t	serialized;

	original.id = 42;
	original.name = "Hello 42";

	std::cout << "Original pointer: " << &original << '\n';
	std::cout << "id: " << original.id << ", name: " << original.name << '\n';

	serialized = Serializer::serialize(&original);
	std::cout << "Serialized: " << serialized << '\n';

	deserialized = Serializer::deserialize(serialized);
	std::cout << "Deserialized pointer: " << deserialized << '\n';

	std::cout << "id: " << deserialized->id
			<< ", name: " << deserialized->name << '\n';

	if (deserialized == &original)
		std::cout << "OK: pointers match!" << '\n';
	else
		std::cout << "KO: pointers differ!" << '\n';

	return (0);
}

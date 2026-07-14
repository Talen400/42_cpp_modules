*This project has been created as part of the 42 curriculum by tlavared.*

# 42 C++ Modules

A collection of C++ modules completed as part of the 42 School common core. Each module introduces progressively more advanced C++ concepts, from basic OOP to templates and STL — all written in C++98.

## Modules

| Module | Topics | Exercises |
|--------|--------|-----------|
| [cpp00](cpp00/) | Classes, member functions, `stdio` streams, initialization lists, `const`, `static` | ex00: Megaphone, ex01: PhoneBook, ex02: Account |
| [cpp01](cpp01/) | Memory allocation, pointers, references, file I/O | ex00–ex06: Zombies, Brain, Weapon, Sed, Harl |
| [cpp02](cpp02/) | Orthodox Canonical Form, operator overloading, Fixed-point numbers | ex00–ex03: Fixed, BSP |
| [cpp03](cpp03/) | Inheritance, constructor/destructor chaining, diamond problem | ex00–ex03: ClapTrap, ScavTrap, FragTrap, DiamondTrap |
| [cpp04](cpp04/) | Subtype polymorphism, abstract classes, interfaces, deep copy | ex00–ex03: Animal, Brain, AMateria |
| [cpp05](cpp05/) | Exceptions, nested classes, try/catch/throw | ex00–ex03: Bureaucrat, Form |
| [cpp06](cpp06/) | C++ casts (static, dynamic, const, reinterpret) | ex00: ScalarConverter, ex01: Serializer, ex02: Identify |
| [cpp07](cpp07/) | Function templates, class templates, generic programming | ex00: swap/min/max, ex01: iter, ex02: Array |
| [cpp08](cpp08/) | STL containers, iterators, algorithms, template specialization | ex00: easyfind, ex01: Span, ex02: MutantStack |
| [cpp09](cpp09/) | STL advanced (map, stack, Ford-Johnson sort), CSV parsing, RPN | ex00: Bitcoin Exchange, ex01: RPN, ex02: PmergeMe |

## Usage

Each exercise has its own directory with a `Makefile`. To compile and run:

```bash
cd cpp00/ex00
make
```

To clean: `make clean`, `make fclean`, `make re`.

## Author

- **tlavared** — 42 Porto

### AI Usage

AI (Claude by Anthropic) was used to generate this README and to assist with understanding C++ concepts throughout the modules. The code, logic, and implementation decisions were made entirely by the author.

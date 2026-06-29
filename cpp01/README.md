*This project has been created as part of the 42 curriculum by tlavared.*

# CPP01 — Memory, References and Pointers to Members

## Description

CPP01 is the second module of the C++ branch at 42. It builds on the foundations of CPP00 by introducing memory management, references, pointers to member functions, and file I/O — all written in C++98.

The module covers six exercises (plus one bonus):

**ex00 — BraiiiiiiinnnzzzZ:** Introduction to stack vs heap allocation using a `Zombie` class. Demonstrates the difference between creating objects with `new`/`delete` (heap) and declaring them as local variables (stack), and how the object's lifetime differs between the two approaches.

**ex01 — Moar brainz!:** Extends the Zombie exercise by allocating an array of objects with `new[]` and freeing it with `delete[]`. Introduces the `setName` setter pattern required when using array allocation, since `new[]` calls the default constructor for each element.

**ex02 — HI THIS IS BRAIN:** A minimal program that demonstrates the relationship between a variable, a pointer to it, and a reference to it — showing that all three share the same memory address.

**ex03 — Unnecessary violence:** Introduces references and pointers as class member attributes through two human classes (`HumanA` and `HumanB`) that hold a `Weapon`. `HumanA` always has a weapon (stored as a reference), while `HumanB` may or may not have one (stored as a pointer). Explores the design implications of each choice.

**ex04 — Sed is for losers:** Implements a file replacement tool using `std::ifstream` and `std::ofstream`. Reads a file entirely into memory, replaces all occurrences of a given string with another using `std::string::find` and `std::string::substr` (without using `std::string::replace`), and writes the result to a new `.replace` file.

**ex05 — Harl 2.0:** Introduces pointers to member functions. A `Harl` class dispatches complaint messages by level (`DEBUG`, `INFO`, `WARNING`, `ERROR`) using arrays of member function pointers — eliminating the need for if/else chains.

**ex06 — Harl filter (bonus):** Extends ex05 with a filter mode: given a log level as a command-line argument, the program prints that level's message and all more severe ones above it. Achieved using switch/case with intentional fallthrough.

---

## Instructions

### Requirements

- C++ compiler with C++98 support (`c++`, `g++`, or `clang++`)
- `make`

### Compilation & Execution

Each exercise has its own directory with a `Makefile`. Navigate to the desired exercise and run:

```bash
make
```

**ex00 — BraiiiiiiinnnzzzZ**
```bash
cd ex00
make
./zombie
```

**ex01 — Moar brainz!**
```bash
cd ex01
make
./zombie
```

**ex02 — HI THIS IS BRAIN**
```bash
cd ex02
make
./this_is_brain
```

**ex03 — Unnecessary violence**
```bash
cd ex03
make
./un_violence
```

**ex04 — Sed is for losers**
```bash
cd ex04
make
./sed_is_for_losers <filename> <s1> <s2>
# Example:
./sed_is_for_losers file.txt hello hi
# Output: file.txt.replace with all occurrences of "hello" replaced by "hi"
```

**ex05 — Harl 2.0**
```bash
cd ex05
make
./harl
```

**ex06 — Harl filter (bonus)**
```bash
cd ex06
make
./harlFilter DEBUG    # prints DEBUG, INFO, WARNING and ERROR
./harlFilter WARNING  # prints only WARNING and ERROR
./harlFilter ERROR    # prints only ERROR
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Resources

### C++ Fundamentals
- cppreference.com — C++ reference
- cplusplus.com — C++ reference and documentation
- learncpp.com — Free C++ tutorial
- *The C++ Programming Language* — Bjarne Stroustrup

### Topics covered in this module
- new and delete operators
- new[] and delete[] for arrays
- References vs pointers
- References and pointers as class members
- std::ifstream and std::ofstream
- std::string::find and std::string::substr
- Pointers to member functions
- switch/case with intentional fallthrough

### AI Usage
AI (Claude by Anthropic) was used to generate this README file and to help understand some C++ concepts throughout the module, such as memory allocation, references, pointers to member functions, and file streams. The code, logic, and implementation decisions were made entirely by the author.

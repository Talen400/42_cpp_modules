*This project has been created as part of the 42 curriculum by tlavared.*

# CPP00 — Introduction to C++

## Description

CPP00 is the first module of the C++ branch at 42. Its goal is to introduce the fundamental concepts of Object-Oriented Programming (OOP) through a series of exercises written in C++98.

The module covers three exercises:

**ex00 — Megaphone:** A simple command-line program that converts all input arguments to uppercase. If no arguments are given, it outputs a loud feedback noise. This exercise introduces basic I/O and string manipulation in C++.

**ex01 — My Awesome PhoneBook:** An interactive phonebook application that stores up to 8 contacts in memory. The user can issue three commands: `ADD` to register a contact (with fields for first name, last name, nickname, phone number, and a darkest secret), `SEARCH` to display a formatted list and look up a contact by index, and `EXIT` to quit. This exercise introduces classes, encapsulation, and formatted output.

**ex02 — The Job Of Your Dreams:** Reconstruction of a lost `Account.cpp` file based on a provided header (`Account.hpp`) and a reference log output. This exercise trains the ability to read and implement a class from its interface and expected behavior alone.

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

**ex00 — Megaphone**
```bash
cd ex00
make
./megaphone hello world
# Output: HELLO WORLD
./megaphone
# Output: * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

**ex01 — PhoneBook**
```bash
cd ex01
make
./phone
# Then use: ADD, SEARCH, EXIT
```

**ex02 — Account**
```bash
cd ex02
make
./account
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
- [cplusplus.com — C++ reference and documentation](https://cplusplus.com/reference/)
- The C++ Programming Language — Bjarne Stroustrup

### Topics covered in this module
- [Strings](http://www.cplusplus.com/reference/string/string/)
- [iomanip](http://www.cplusplus.com/reference/iomanip/)

### AI Usage
AI (Claude by Anthropic) was used to generate this README file and to help understand some C++ concepts, such as static member functions and variables. The code, logic, and implementation decisions were made entirely by the author.

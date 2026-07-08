*This project has been created as part of the 42 curriculum by tlavared.*

# CPP05 — Exceptions

## Description

CPP05 is the sixth module of the C++ branch at 42. It introduces exception handling in C++98 through a bureaucratic simulation — custom exception classes, try/catch blocks, exception propagation up the call stack, and the Factory design pattern.

The module covers four exercises:

**ex00 — Bureaucrat:** Implements a `Bureaucrat` class with a `const` name and a grade (1–150). The constructor validates the grade and throws custom `GradeTooHighException` or `GradeTooLowException` (both nested inside `Bureaucrat`) when the grade is out of range. The `upGrade()` and `downGrade()` methods increment or decrement the grade, throwing if the limit would be exceeded. This exercise introduces custom exception classes as inner classes inheriting from `std::exception`.

**ex01 — Form:** Adds a `Form` class with a name, a signed flag, and two const grade thresholds (required to sign and to execute). `Form::beSigned(Bureaucrat&)` throws `GradeTooLowException` if the bureaucrat's grade is insufficient. `Bureaucrat::signForm(Form&)` calls `beSigned()` and prints success or failure. This exercise demonstrates passing exceptions between classes and exception-safe state management.

**ex02 — No, you need form 28B, not 28C...:** Refactors `Form` into an abstract class `AForm` with a pure virtual `execute()` method. Three concrete forms are introduced: `ShrubberyCreationForm` (creates an ASCII tree file), `RobotomyRequestForm` (randomly robotomizes with 50% success rate), and `PresidentialPardonForm` (pardons by Zaphod Beeblebrox). `Bureaucrat::executeForm()` calls `form.execute()` with proper exception handling. The `AForm` hierarchy uses a richer exception set including `FormHasSigned` and `FormHasNotSigned`.

**ex03 — At least this beats coffee-making:** Implements the Factory pattern via an `Intern` class. The `Intern::makeForm()` method takes a form name string and a target string, matches the name against known types using a static array of `FormEntry` structs, and returns a dynamically allocated `AForm*`. Unknown names throw `AForm::FormInvalid`. This demonstrates function pointers, lookup tables, and decoupling object creation from client code.

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

**ex00 — Bureaucrat**
```bash
cd ex00
make
./bureaucrat
```

**ex01 — Form**
```bash
cd ex01
make
./form
```

**ex02 — Abstract Form**
```bash
cd ex02
make
./shrubbery
```

**ex03 — Intern**
```bash
cd ex03
make
./intern
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Key Concepts

### Exception Handling

Exceptions provide a way to transfer control from a point of error detection to a handler higher up the call stack. In C++, a `throw` expression transfers control to the nearest enclosing `try` block whose `catch` handler matches the exception type. If no handler is found, `std::terminate()` is called.

### Custom Exception Classes

Custom exceptions are created by inheriting from `std::exception` and overriding the `what()` virtual method. By nesting them inside the class that throws them (e.g., `Bureaucrat::GradeTooHighException`), the exception is naturally scoped and named in context.

### Exception Safety

When a constructor throws, the object is considered not fully constructed — its destructor is not called. Any resources already acquired before the throw must be manually released in the constructor itself (the RAII pattern avoids this problem by binding resources to object lifetimes).

### Abstract Classes with Pure Virtual Functions

A pure virtual function (`= 0`) has no implementation in the base class. A class with at least one pure virtual function is abstract and cannot be instantiated. Derived classes must override the pure virtual to become concrete. This enforces a contract across the hierarchy.

### Factory Pattern

The Factory pattern encapsulates object creation behind a common interface. The `Intern` receives a string and returns the correct `AForm*` subtype without the caller needing to know which concrete class was instantiated. This decouples creation logic from business logic and makes adding new form types straightforward.

---

## Resources

### C++ Fundamentals
- cppreference.com — C++ reference
- cplusplus.com — C++ reference and documentation
- *The C++ Programming Language* — Bjarne Stroustrup

### Topics covered in this module
- Custom exception classes (`std::exception` inheritance)
- `throw`, `try`, `catch` control flow
- Exception propagation through the call stack
- Nested exception classes
- Abstract base classes with pure virtual functions
- Function pointers and lookup tables
- Factory design pattern
- Exception safety in constructors

### AI Usage
AI (Claude by Anthropic) was used to generate this README file and to help understand C++ concepts throughout the module, such as exception handling, abstract classes, and the Factory pattern. The code, logic, and implementation decisions were made entirely by the author.

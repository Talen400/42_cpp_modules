*This project has been created as part of the 42 curriculum by tlavared.*

# CPP07 — Templates

## Description

CPP07 is the eighth module of the C++ branch at 42. It introduces **templates** — C++'s mechanism for writing generic, type-independent code through function templates and class templates, all in C++98.

The module covers three exercises:

**ex00 — Start with some functions:** Implements three function templates (`swap`, `min`, `max`) that work with any type supporting comparison operators. `swap` exchanges two values, `min` returns the smaller (or the second if equal), and `max` returns the larger (or the second if equal). All templates are defined entirely in the header file, demonstrating how the compiler instantiates template code at the call site.

**ex01 — Iter:** Implements a function template `iter` that takes an array address, a length, and a function to apply to each element. Works with any array type and supports both `const` and non-const element access via template parameter deduction.

**ex02 — Array:** Develops a class template `Array<T>` with dynamic allocation using `new[]`, deep copy semantics, bounds-checked subscript operator, and a `size()` member. The class follows the Orthodox Canonical Form and throws `std::exception` on out-of-bounds access.

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

**ex00 — Function Templates**
```bash
cd ex00
make
./whatever
```

**ex01 — Iter**
```bash
cd ex01
make
./iter
```

**ex02 — Array**
```bash
cd ex02
make
./array
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Key Concepts

### Function Templates

Function templates allow writing a single function that works with any type. The compiler generates a concrete instantiation for each type the template is called with. Template definitions must reside in headers because the compiler needs the full definition at the point of instantiation.

### Class Templates

Class templates generalize the concept to types, enabling generic containers like `Array<T>`. Member functions defined outside the class body require the `template <typename T>` prefix and `ClassName<T>::` qualification.

### Value Initialization

Using `new T[n]()` (with trailing parentheses) value-initializes each element — fundamental types are zeroed, and class types have their default constructor called. Without the parentheses, elements of fundamental types are left uninitialized.

### Deep Copy

When a class manages dynamic memory, the default shallow copy (copying the pointer) leads to double-free and aliasing issues. Deep copy allocates independent storage and copies each element, ensuring copies are fully independent.

---

## Resources

### Topics covered in this module

- Function templates (`template <typename T>`)
- Class templates (`template <typename T> class`)
- Template instantiation and compilation model
- Deep copy vs shallow copy
- Value initialization with `new T[n]()`
- Array decay to pointer
- `const`-correctness in generic code
- Orthodox Canonical Form for template classes

### AI Usage

AI (Claude by Anthropic) was used to generate this README file. The code, logic, and implementation decisions were made entirely by the author.

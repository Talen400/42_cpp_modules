*This project has been created as part of the 42 curriculum by tlavared.*

# CPP04 — Subtype Polymorphism, Abstract Classes and Interfaces

## Description

CPP04 is the fifth module of the C++ branch at 42. It builds on the inheritance concepts of CPP03 by introducing subtype polymorphism through virtual functions, abstract classes with pure virtual functions, and interfaces — all written in C++98.

The module covers four exercises:

**ex00 — Polymorphism:** Introduces virtual functions and subtype polymorphism. An `Animal` base class declares `makeSound()` as `virtual`, allowing `Dog` and `Cat` to override it with their own sounds. A `WrongAnimal`/`WrongCat` pair demonstrates the contrast: without `virtual`, calling `makeSound()` through a base pointer always invokes the base version, regardless of the actual object type. The virtual destructor is also introduced to ensure correct destruction when deleting derived objects through base pointers.

**ex01 — I don't want to set the world on fire:** Extends the `Animal` hierarchy by adding a `Brain` class containing an array of 100 idea strings, allocated on the heap. `Dog` and `Cat` each own a `Brain*` pointer, allocated in their constructor and deleted in their destructor. Deep copy is enforced in both the copy constructor and `operator=` — the `Brain` is cloned with `new Brain(*other._brain)` rather than copying the pointer, preventing double-free errors and shared state between copies.

**ex02 — Abstract class:** Makes `Animal` an abstract class by declaring `makeSound()` as a pure virtual function (`= 0`). This prevents direct instantiation of `Animal` while still allowing `Dog` and `Cat` to be used polymorphically through `Animal*` pointers. The `Brain` deep copy behavior from ex01 is preserved.

**ex03 — Interface & recap:** Implements a full interface-based system using pure abstract classes. `AMateria` is an abstract base for spell materials with a pure virtual `clone()` method. `Ice` and `Cure` are concrete implementations with specific `use()` messages. `ICharacter` and `IMateriaSource` are pure interfaces (no data, all pure virtual). `Character` implements `ICharacter` with a 4-slot inventory of `AMateria*`, with full deep copy semantics using `clone()`. `MateriaSource` implements `IMateriaSource`, storing up to 4 learned templates and cloning them on demand via `createMateria()`. The `unequip()` function intentionally does not delete materias, placing memory management responsibility on the caller.

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

**ex00 — Polymorphism**
```bash
cd ex00
make
./poly
```

**ex01 — I don't want to set the world on fire**
```bash
cd ex01
make
./brain
```

**ex02 — Abstract class**
```bash
cd ex02
make
./abstract
```

**ex03 — Interface & recap**
```bash
cd ex03
make
./amateria
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Key Concepts

### Virtual Functions and Subtype Polymorphism

A `virtual` function allows the correct derived implementation to be called even when the object is accessed through a base class pointer. Without `virtual`, the compiler resolves the call at compile time based on the pointer type — always calling the base version. With `virtual`, the call is resolved at runtime based on the actual type of the object. This is subtype polymorphism.

### Virtual Destructor

When deleting a derived object through a base pointer, a non-virtual destructor calls only the base destructor — leaking any resources the derived class owns. Declaring the base destructor `virtual` ensures the correct destructor chain fires regardless of pointer type.

### Abstract Classes and Pure Virtual Functions

A pure virtual function (`= 0`) has no implementation in the base class and must be overridden by any concrete derived class. A class with at least one pure virtual function is abstract and cannot be instantiated directly. This enforces a contract: any class claiming to be an `Animal` must define what sound it makes.

### Deep Copy with Heap-Allocated Members

When a class owns a pointer to heap memory, the compiler-generated copy constructor and `operator=` perform a shallow copy — both objects end up pointing to the same memory. When either is destroyed, the other holds a dangling pointer. Deep copy solves this by allocating a new object and copying the contents: `new Brain(*other._brain)`.

### Interfaces via Pure Abstract Classes

C++98 has no `interface` keyword, but the pattern is achieved with a class containing only pure virtual functions and a virtual destructor. Concrete classes implement all functions, and the interface type is used as the polymorphic handle. Forward declarations (`class ICharacter;`) break circular dependencies between headers.

### clone() Pattern

When the concrete type of an object is unknown at the point of copying, a virtual `clone()` method allows each class to copy itself correctly. `clone()` returns a `new` instance of the same derived type, enabling deep copy of polymorphic collections without knowing the concrete type.

---

## Resources

### C++ Fundamentals
- cppreference.com — C++ reference
- cplusplus.com — C++ reference and documentation
- *The C++ Programming Language* — Bjarne Stroustrup

### Topics covered in this module
- Virtual functions and subtype polymorphism
- Virtual destructors
- Abstract classes and pure virtual functions (`= 0`)
- Deep copy with heap-allocated members
- Pure abstract classes as interfaces
- Forward declarations to resolve circular dependencies
- The `clone()` virtual copy pattern
- Memory management with polymorphic inventories

### AI Usage
AI (Claude by Anthropic) was used to generate this README file and to help understand C++ concepts throughout the module, such as virtual functions, abstract classes, deep copy semantics, and the interface pattern. The code, logic, and implementation decisions were made entirely by the author.

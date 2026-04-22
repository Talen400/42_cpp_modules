*This project has been created as part of the 42 curriculum by tlavared.*

# CPP03 — Inheritance

## Description

CPP03 is the fourth module of the C++ branch at 42. It introduces inheritance, constructor/destructor chaining, and the diamond inheritance problem — all written in C++98.

The module covers four exercises:

**ex00 — ClapTrap:** Introduces the base class `ClapTrap` in Orthodox Canonical Form. The class has private attributes (`_name`, `_hitPoint`, `_energyPoint`, `_attackDamage`) and three member functions: `attack()`, `takeDamage()`, and `beRepaired()`. Each action costs or consumes energy or hit points, and the object cannot act when dead or out of energy.

**ex01 — Serena, my love!:** Introduces `ScavTrap`, a class that inherits publicly from `ClapTrap`. Demonstrates constructor and destructor chaining — when a `ScavTrap` is created, the `ClapTrap` constructor fires first, and destruction occurs in reverse order. `ScavTrap` overrides `attack()` with its own message and adds the `guardGate()` special ability. ClapTrap attributes are changed to `protected` to allow access from derived classes.

**ex02 — Repetitive work:** Introduces `FragTrap`, a second class inheriting from `ClapTrap`, following the same chaining pattern. `FragTrap` has different attribute values (100 hp, 100 energy, 30 damage) and its own special ability `highFivesGuy()`. Reinforces the inheritance pattern established in ex01.

**ex03 — Now DiamondTrap:** Creates `DiamondTrap`, which inherits from both `ScavTrap` and `FragTrap` — introducing the diamond inheritance problem. Without intervention, two separate `ClapTrap` instances would exist inside `DiamondTrap`. This is resolved using `virtual public` inheritance in both `ScavTrap` and `FragTrap`, ensuring a single shared `ClapTrap` base. `DiamondTrap` is responsible for directly initializing `ClapTrap` in its constructor. It has its own private `_name` (same variable name as `ClapTrap`), with `ClapTrap::_name` set to the constructor parameter + `"_clap_name"`. The `whoAmI()` function prints both names.

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

**ex00 — ClapTrap**
```bash
cd ex00
make
./clap
```

**ex01 — ScavTrap**
```bash
cd ex01
make
./scav
```

**ex02 — FragTrap**
```bash
cd ex02
make
./frag
```

**ex03 — DiamondTrap**
```bash
cd ex03
make
./diamond
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Key Concepts

### Inheritance

A derived class inherits all `public` and `protected` members of its base class. Constructors and destructors are not inherited directly — the base constructor must be explicitly called in the derived class's initializer list. Construction always goes from base to derived; destruction always goes in reverse.

### protected vs private

Members declared `private` are inaccessible to derived classes. Changing them to `protected` allows derived classes to read and modify them directly, while keeping them hidden from external code.

### Constructor/Destructor Chaining

When a derived object is created, the base class constructor fires first, then the derived. On destruction, the derived destructor fires first, then the base. This order ensures that the object is always fully initialized before derived-specific code runs, and fully cleaned up before the base is destroyed.

### Diamond Inheritance

When two classes (`ScavTrap` and `FragTrap`) each inherit from the same base (`ClapTrap`), and a third class (`DiamondTrap`) inherits from both, the base is duplicated by default — two separate `ClapTrap` instances exist inside `DiamondTrap`, causing ambiguity. Virtual inheritance (`virtual public ClapTrap`) in both intermediate classes resolves this by sharing a single `ClapTrap` instance. When virtual inheritance is used, the most derived class (`DiamondTrap`) is responsible for directly calling the `ClapTrap` constructor.

---

## Resources

### C++ Fundamentals
- cppreference.com — C++ reference
- cplusplus.com — C++ reference and documentation
- learncpp.com — Free C++ tutorial
- *The C++ Programming Language* — Bjarne Stroustrup

### Topics covered in this module
- Public inheritance
- `protected` access specifier
- Constructor and destructor chaining
- Member function overriding
- Multiple inheritance
- Diamond inheritance problem
- Virtual inheritance (`virtual public`)
- Most-derived class responsibility for virtual base initialization

### AI Usage
AI (Claude by Anthropic) was used to generate this README file and to help understand C++ concepts throughout the module, such as inheritance chaining, the diamond problem, and virtual inheritance. The code, logic, and implementation decisions were made entirely by the author.

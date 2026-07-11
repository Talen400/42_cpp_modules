*This project has been created as part of the 42 curriculum by tlavared.*

# CPP08 — STL: Containers, Iterators, Algorithms

## Description

CPP08 is the ninth module of the C++ branch at 42. It introduces the **Standard Template Library (STL)** — containers, iterators, and algorithms that enable generic, efficient, and reusable code in C++98. Finally you are allowed to use `std::vector`, `std::list`, `<algorithm>`, and everything the STL has to offer.

The module covers three exercises:

**ex00 — Easy find:** Implements a function template `easyfind` that searches for an integer in any sequential container (vector, list, deque) using `std::find`, and throws an exception if not found. Demonstrates `typename` for dependent types and const/non-const iterator overloads.

**ex01 — Span:** Develops a `Span` class that stores up to N integers and computes the shortest and longest distance (span) between any two numbers. Uses `std::sort` and `std::min_element`/`std::max_element` for efficient computation. Supports adding multiple numbers at once via iterator ranges, and is tested with 20,000+ random numbers.

**ex02 — MutantStack:** Creates a `MutantStack` class that inherits from `std::stack` and exposes the underlying container's iterators by accessing the protected `c` member. Provides `begin()`, `end()`, `rbegin()`, `rend()` — making `std::stack` iterable for the first time. The output matches `std::list` exactly when traversed.

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

**ex00 — Easy find**
```bash
cd ex00
make
./easyfind
```

**ex01 — Span**
```bash
cd ex01
make
./span
```

**ex02 — MutantStack**
```bash
cd ex02
make
./mutantstack
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Key Concepts

### STL Three-Pillar Architecture

The STL is built on containers (where data lives), iterators (how you traverse), and algorithms (what you do). Containers like `vector`, `list`, `deque` provide iterators that algorithms like `std::find`, `std::sort`, and `std::minmax_element` consume — all without knowing each other's concrete types.

### Container Adapters

`std::stack` and `std::queue` are not containers — they are *adapters* that wrap an underlying container (default: `std::deque`) and expose a restricted interface. They deliberately hide iterators. `MutantStack` overcomes this via inheritance, accessing the protected `c` member to expose iteration.

### Iterator Categories

Different containers support different iterator categories: `vector`/`deque` provide random-access iterators (supports `+`, `-`, `[]`), `list` provides bidirectional iterators (`++`, `--`), and `stack` (as an adapter) provides none — until `MutantStack` exposes them.

### Dependent Types with `typename`

When a type depends on a template parameter (e.g., `T::iterator`), the `typename` keyword is required to tell the compiler it's a type, not a static member. This is essential in `easyfind` and in any generic code dealing with STL containers.

---

## Resources

### Topics covered in this module

- STL containers (`vector`, `list`, `deque`)
- Container adapters (`stack`)
- Iterator categories and usage
- STL algorithms (`find`, `sort`, `min_element`, `max_element`)
- Template-dependent types with `typename`
- Const-correctness in generic functions
- Container adapter pattern and inheritance
- Protected member access (`c` in `std::stack`)

### AI Usage

AI (Claude by Anthropic) was used to generate this README file. The code, logic, and implementation decisions were made entirely by the author.

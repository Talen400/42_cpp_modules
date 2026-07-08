*This project has been created as part of the 42 curriculum by tlavared.*

# CPP06 — Casts

## Description

CPP06 is the seventh module of the C++ branch at 42. It is entirely focused on **type casts** — the four C++ cast operators, when to use each one, and why they exist instead of the old C-style `(type)` cast. The module enforces modern C++ casts through the `-Wold-style-cast` compiler flag (which turns C-style casts into errors under `-Werror`).

The module covers three exercises:

**ex00 — ScalarConverter:** Implements a non-instantiable `ScalarConverter` class with a single static `convert(const std::string&)` method. The program reads a string from the command line and prints its value converted to `char`, `int`, `float`, and `double`. The string may represent a char (quoted or single character), an int, a float (trailing `f`), a double, or a pseudo-literal (`nan`, `inf`, `+inf`, `-inf`, and their `f` variants). The value is first parsed into a universal `double` (using `strtod`), then converted to each target type with `static_cast`, handling special cases such as NaN, infinity, non-displayable characters, and out-of-range values (`std::numeric_limits`, `std::isnan`, `std::isinf`, `std::isprint`).

**ex01 — Serializer:** Implements a non-instantiable `Serializer` class with two static methods: `serialize(Data* ptr)` converting a pointer to a `uintptr_t`, and `deserialize(uintptr_t raw)` converting it back. Both use `reinterpret_cast` to reinterpret the pointer's bits as an integer and back. A non-empty `Data` struct (`id` and `name`) serves as the payload. The exercise demonstrates that a pointer is literally a memory address stored as a number, and that `reinterpret_cast` — not `static_cast` — is required to reinterpret bits between unrelated types. `uintptr_t` (from `<stdint.h>`) is used because it is guaranteed to be large enough to hold any pointer.

**ex02 — Identify:** Implements a `Base` class (with a virtual destructor, enabling RTTI) and three derived classes `A`, `B`, and `C`. The `generate()` function randomly returns a `Base*` to a new `A`, `B`, or `C`. The `identify()` function is implemented twice: once taking a `Base*` (using `dynamic_cast` on pointers, which returns `NULL` on failure) and once taking a `Base&` (using `dynamic_cast` on references, which throws `std::bad_cast` on failure — caught with `try/catch`). The exercise demonstrates run-time type identification (RTTI) and the difference in failure behavior between pointer and reference `dynamic_cast`.

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

**ex00 — ScalarConverter**
```bash
cd ex00
make
./converter 42.0f
```

**ex01 — Serializer**
```bash
cd ex01
make
./serializer
```

**ex02 — Identify**
```bash
cd ex02
make
./identify
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Key Concepts

### C++ Cast Operators

C++ provides four named cast operators that make the intent explicit and give the compiler a chance to catch mistakes. The old C-style `(type)` cast can perform any conversion and silently hides intent; under this module it is forbidden (`-Wold-style-cast`).

| Cast | Timing | Safety | Purpose | On failure |
|------|--------|--------|---------|------------|
| `static_cast` | Compile time | Medium | Convert values between related types | Compile error |
| `dynamic_cast` | Run time | High | Query an object's real type in a hierarchy | `NULL` (pointer) or `std::bad_cast` (reference) |
| `reinterpret_cast` | Compile time | None | Reinterpret the bit pattern as another type | Undefined behavior |

### static_cast — Value Conversion

`static_cast` performs well-defined conversions between related types at compile time (e.g. numeric conversions, upcasts in a hierarchy, `void*` to a concrete pointer). It converts the *value* rather than reinterpreting bits. It is used in ex00 to turn the universal `double` into `char`, `int`, and `float`.

### reinterpret_cast — Bit Reinterpretation

`reinterpret_cast` performs a low-level reinterpretation of the bit pattern of its operand. It is the only cast able to turn a pointer into an integer (`uintptr_t`) and back, which is what serialization requires. It carries no safety guarantees — undefined behavior is possible if the resulting value is misused.

### dynamic_cast — Run-Time Type Identification (RTTI)

`dynamic_cast` safely navigates a class hierarchy, asking at run time "is this object really of type T?". For it to work, the base class must have at least one virtual function (here, a virtual destructor), which makes the compiler emit RTTI. On a pointer it returns `NULL` if the cast fails; on a reference it throws `std::bad_cast`, because references can never be null.

### Virtual Destructor and Polymorphic Destruction

A virtual destructor in `Base` does two things: it enables RTTI (required by `dynamic_cast`) and it guarantees that deleting a derived object through a base pointer calls the derived destructor first, preventing resource leaks.

### Pseudo-Literals and Parsing

Special float/double values (`nan`, `inf`, `+inf`, `-inf` and their `f` variants) cannot be written as ordinary numeric literals. `strtod` understands them, and `std::isnan` / `std::isinf` detect them — they cannot be compared with `==` because NaN is never equal to anything, including itself.

---

## Resources

### C++ Fundamentals
- cppreference.com — C++ reference
- cplusplus.com — C++ reference and documentation
- *The C++ Programming Language* — Bjarne Stroustrup

### Topics covered in this module
- `static_cast`, `dynamic_cast`, `reinterpret_cast` (and `const_cast`)
- `-Wold-style-cast` and the prohibition of C-style casts
- Parsing strings to numeric types with `strtod`
- `std::numeric_limits`, `std::isnan`, `std::isinf`, `std::isprint`
- `uintptr_t` and pointer-to-integer serialization
- Run-Time Type Identification (RTTI) and virtual destructors
- Pointer vs. reference `dynamic_cast` failure behavior (`NULL` vs `std::bad_cast`)
- `try` / `catch` exception handling for references

### AI Usage
AI (Claude by Anthropic) was used to generate this README file and to help understand C++ concepts throughout the module, such as the four cast operators, `uintptr_t` serialization, and RTTI. The code, logic, and implementation decisions were made entirely by the author.

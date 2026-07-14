*This project has been created as part of the 42 curriculum by tlavared.*

# CPP09 — STL Avançado

## Description

CPP09 is the tenth and final module of the C++ branch at 42. It puts the STL to work on three real-world problems, each requiring a different standard container — and once a container is used, it cannot be reused in later exercises.

The module covers three exercises:

**ex00 — Bitcoin Exchange:** Builds a program (`btc`) that reads a CSV database of Bitcoin exchange rates and an input file with dates and values. For each valid entry, it multiplies the value by the exchange rate for that date — or the closest prior date if the exact date is not found. Uses `std::map` for ordered date→rate lookup with `lower_bound` for nearest-date search.

**ex01 — RPN:** Implements a Reverse Polish Notation calculator (`RPN`) using `std::stack`. The expression is passed as a single argument; numbers are single digits (0–9), operators are `+ - * /`. Handles division by zero, insufficient operands, and malformed tokens.

**ex02 — PmergeMe:** Implements the Merge-Insert sort (Ford-Johnson algorithm) using two different containers (`std::vector` and `std::deque`) and measures the execution time of each. The program accepts a sequence of positive integers and displays the unsorted sequence, the sorted result, and the processing time for each container in microseconds.

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

**ex00 — Bitcoin Exchange**
```bash
cd ex00
make
./btc input.txt
```

A sample `data.csv` is included. The input file should have the format:
```
date | value
2011-01-03 | 3
```

**ex01 — RPN**
```bash
cd ex01
make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

**ex02 — PmergeMe**
```bash
cd ex02
make
./PmergeMe 3 5 9 7 4
```

To clean compiled objects:
```bash
make clean   # removes .o files
make fclean  # removes .o files and binary
make re      # full recompile
```

---

## Key Concepts

### Container Uniqueness Rule

Each exercise must use a container not used in any previous exercise. The constraint forces thoughtful container selection:
- `ex00` uses `std::map` (ordered key-value lookup, `lower_bound`)
- `ex01` uses `std::stack` (LIFO for RPN evaluation)
- `ex02` uses `std::vector` and `std::deque` (merge sort on two containers)

### std::map and lower_bound

`std::map` stores key-value pairs sorted by key. `lower_bound(key)` returns an iterator to the first element whose key is not less than the search key — essential for finding the closest prior date when an exact match doesn't exist.

### RPN with std::stack

Reverse Polish Notation eliminates parentheses by placing operators after their operands. A stack naturally models the computation: push operands, pop two for each operator, push the result back.

### Merge-Insert Sort (Ford-Johnson)

The Ford-Johnson algorithm pairs elements, sorts the larger elements recursively, then inserts the smaller elements using binary search in Jacobsthal order. It minimizes the number of comparisons in the worst case. The practical implementation uses merge sort with a small threshold for insertion sort.

### Timing with gettimeofday

`gettimeofday()` from `<sys/time.h>` provides microsecond precision for comparing the performance of different containers on the same sorting algorithm.

---

## Resources

### Topics covered in this module

- `std::map` with `lower_bound` / `upper_bound`
- `std::stack` for expression evaluation
- `std::vector` vs `std::deque` performance characteristics
- Merge-Insert sort (Ford-Johnson algorithm)
- CSV parsing with `<fstream>` and `<sstream>`
- Date validation and error handling
- Microsecond timing with `gettimeofday()`

### AI Usage

AI (Claude by Anthropic) was used to generate this README file. The code, logic, and implementation decisions were made entirely by the author.

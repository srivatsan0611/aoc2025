# Day 6: Trash Compactor

[Problem Link](https://adventofcode.com/2025/day/6)

## Problem Statement

The cephalopods have been working on complex math problems arranged in a unique vertical format. Your task is to parse a vertical math worksheet where problems are arranged in columns, calculate each problem's result, and sum all results for a grand total.

**Input Format:**
- Problems are arranged in columns separated by spaces
- Each problem has numbers stacked vertically
- The operation (* or +) appears at the bottom of each column
- Numbers in a column should be combined using the specified operation from top to bottom

---

## Part 1

**Goal:** Parse the vertical math worksheet, calculate each problem's result, and find the sum of all results.

### Example

Given:
```
123 328  51 64
 45 64  387 23
  6 98  215 314
*   +   *   +
```

This represents 4 problems:
- Problem 1: 123 * 45 * 6 = 33210
- Problem 2: 328 + 64 + 98 = 490
- Problem 3: 51 * 387 * 215 = 4243455
- Problem 4: 64 + 23 + 314 = 401

**Grand total: 4277556**

### Approach

1. Parse the input to identify columns (problems)
2. For each column, collect all numbers from top to bottom
3. Identify the operation from the last row
4. Calculate the result by applying the operation sequentially
5. Sum all problem results to get the grand total

**Key Details:**
- Problems are separated by columns of spaces
- Numbers can have varying widths
- Use `long long` to handle potentially large results (especially for multiplication)

---

## Part 2

**Goal:** Parse the vertical math worksheet using the correct cephalopod math format (right-to-left, vertical digits), calculate each problem's result, and find the sum of all results.

### Example

Given the same input as Part 1:
```
123 328  51 64
 45 64  387 23
  6 98  215 314
*   +   *   +
```

But now reading right-to-left with each column as a vertical number (top = most significant digit):
- Rightmost problem: 4 + 431 + 623 = 1058
- Second from right: 175 * 581 * 32 = 3253600
- Third from right: 8 + 248 + 369 = 625
- Leftmost: 356 * 24 * 1 = 8544

**Grand total: 3263827**

### Approach

1. Parse input and process columns from right-to-left
2. For each column, read digits vertically to form a number (top-to-bottom = most-to-least significant)
3. Group consecutive non-space columns into problems (problem ends when operation symbol is found)
4. Apply the operation to all numbers in each problem
5. Sum all problem results to get the grand total

**Key Details:**
- Columns are processed right-to-left (reverse order from Part 1)
- Each column represents a vertical number with digits stacked top-to-bottom
- Problems are still separated by space-only columns
- Need to handle digit-to-number conversion for vertical columns

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day6/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Compile Part 2
cd Day6/part2 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 (default input)
./Day6/part1/solution

# Run Part 1 with example
./Day6/part1/solution Day6/example.txt

# Run Part 2 (default input)
./Day6/part2/solution

# Run Part 2 with example
./Day6/part2/solution Day6/example.txt
```

## Structure

```
Day6/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution
```

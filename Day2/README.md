# Day 2: Gift Shop

[Problem Link](https://adventofcode.com/2025/day/2)

## Problem Statement

A gift shop database has invalid product IDs that need to be identified. The young Elf was playing with the computer and created IDs based on silly repeating patterns. Your job is to find all invalid IDs within given ranges and sum them up.

---

## Part 1

**Goal:** Find all IDs that are made of **a sequence repeated exactly twice**.

### Valid Examples
- `55` (5 twice) - **invalid**
- `6464` (64 twice) - **invalid**
- `123123` (123 twice) - **invalid**
- `101` (no repeating pattern) - **valid**

### Invalid IDs Rule
An ID is invalid if its digits form a pattern that repeats exactly 2 times. The number must have even length and the first half must equal the second half.

### Example

Given ranges: `11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124`

```
11-22           → Invalid IDs: 11, 22
95-115          → Invalid IDs: 99
998-1012        → Invalid IDs: 1010
1188511880-1188511890 → Invalid IDs: 1188511885
222220-222224   → Invalid IDs: 222222
1698522-1698528 → No invalid IDs
446443-446449   → Invalid IDs: 446446
38593856-38593862 → Invalid IDs: 38593859
565653-565659   → No invalid IDs
824824821-824824827 → No invalid IDs
2121212118-2121212124 → No invalid IDs
```

**Example Answer: 1227775554**

### Approach

1. Parse comma-separated ranges (start-end)
2. For each ID in each range:
   - Convert to string
   - Check if length is even
   - Compare first half with second half
   - If equal, it's invalid
3. Sum all invalid IDs

**Answer:** `18893502033` ⭐

---

## Part 2

**Goal:** Find all IDs that are made of **a sequence repeated at least twice**.

### Updated Rule
An ID is invalid if its digits form a repeating pattern that repeats 2 or more times. For example:
- `55` (5 × 2 times) - **invalid**
- `111` (1 × 3 times) - **invalid**
- `12341234` (1234 × 2 times) - **invalid**
- `123123123` (123 × 3 times) - **invalid**
- `1212121212` (12 × 5 times) - **invalid**

### Example

Same ranges, but now counting patterns repeated 2+ times:

```
11-22           → Invalid IDs: 11, 22
95-115          → Invalid IDs: 99, 111 (1 repeated 3 times)
998-1012        → Invalid IDs: 999, 1010
1188511880-1188511890 → Invalid IDs: 1188511885
222220-222224   → Invalid IDs: 222222
1698522-1698528 → No invalid IDs
446443-446449   → Invalid IDs: 446446
38593856-38593862 → Invalid IDs: 38593859
565653-565659   → Invalid IDs: 565656
824824821-824824827 → Invalid IDs: 824824824
2121212118-2121212124 → Invalid IDs: 2121212121
```

**Example Answer: 4174379265**

### Approach

1. Parse comma-separated ranges
2. For each ID in each range:
   - Try all possible pattern lengths from 1 to length/2
   - For each pattern length that divides the ID length evenly:
     - Extract the pattern (first `period` digits)
     - Check if the entire ID is this pattern repeated
     - If repeats ≥ 2, it's invalid
3. Sum all invalid IDs

**Answer:** `26202168557` ⭐

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day2/part1 && g++ -o solution solution.cpp && cd ../..

# Compile Part 2
cd Day2/part2 && g++ -o solution solution.cpp && cd ../..

# Run Part 1 (default input)
./Day2/part1/solution

# Run Part 1 with example
./Day2/part1/solution Day2/example.txt

# Run Part 2 (default input)
./Day2/part2/solution

# Run Part 2 with example
./Day2/part2/solution Day2/example.txt
```

## Structure

```
Day2/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   ├── solution.cpp # Part 1 solution
│   └── solution     # Compiled executable
└── part2/
    ├── solution.cpp # Part 2 solution
    └── solution     # Compiled executable
```

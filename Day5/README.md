# Day 5: Cafeteria

[Problem Link](https://adventofcode.com/2025/day/5)

## Problem Statement

After breaking through the wall, the Elves discover a cafeteria! However, the kitchen is in chaos due to a new inventory management system that makes it difficult to determine which ingredients are fresh versus spoiled.

The database consists of:
1. **Fresh ingredient ID ranges** (inclusive, can overlap)
2. A blank line separator
3. **Available ingredient IDs** to check

An ingredient ID is **fresh** if it falls within any of the specified ranges.

---

## Part 1

**Goal:** Count how many of the available ingredient IDs are fresh.

### Example

Given:
```
3-5
10-14
16-20
12-18

1
5
8
11
17
32
```

Analysis:
- Ingredient ID **1** is spoiled (not in any range)
- Ingredient ID **5** is fresh (falls in range 3-5)
- Ingredient ID **8** is spoiled (not in any range)
- Ingredient ID **11** is fresh (falls in range 10-14)
- Ingredient ID **17** is fresh (falls in ranges 16-20 and 12-18)
- Ingredient ID **32** is spoiled (not in any range)

**Answer: 3** fresh ingredients.

### Approach

1. Parse all fresh ID ranges from the input file (format: `start-end`)
2. Read each available ingredient ID after the blank line
3. For each ID, check if it falls within any range (inclusive)
4. Count how many IDs are fresh

**Key Details:**
- Ranges are inclusive: `3-5` means IDs 3, 4, and 5 are all fresh
- Ranges can overlap: an ID is fresh if it's in ANY range
- Use `long long` to handle large ingredient ID numbers

---

## Part 2

**Goal:** Count the total number of unique ingredient IDs considered fresh across all ranges.

### Key Difference

Part 2 ignores the available ingredient IDs section entirely. Instead, we need to count all IDs that fall within the fresh ranges.

### Example

Using the same ranges:
```
3-5
10-14
16-20
12-18
```

The fresh IDs are: 3, 4, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20

**Answer: 14** total fresh ingredient IDs.

### Approach

1. Parse all fresh ID ranges
2. Sort ranges by start position
3. Merge overlapping or adjacent ranges to avoid double-counting
   - Example: ranges `10-14` and `12-18` overlap, becoming `10-18` (9 IDs, not 5+7=12)
4. For each merged range, count IDs: `(end - start + 1)`
5. Sum all counts

**Key Details:**
- Overlapping ranges must be merged: `10-14` + `12-18` = `10-18` (9 unique IDs)
- Adjacent ranges should also merge: `3-5` + `6-10` = `3-10` (8 IDs)
- The counts can be very large (350+ trillion for the actual input)

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day5/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Compile Part 2
cd Day5/part2 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 (default input)
./Day5/part1/solution

# Run Part 1 with example
./Day5/part1/solution Day5/example.txt

# Run Part 2 (default input)
./Day5/part2/solution

# Run Part 2 with example
./Day5/part2/solution Day5/example.txt
```

## Structure

```
Day5/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution
```

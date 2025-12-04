# Day 4: Printing Department

[Problem Link](https://adventofcode.com/2025/day/4)

## Problem Statement

You're in the printing department trying to find a way deeper into the North Pole base. The Elves want to use forklifts to break through a wall, but the forklifts are busy moving large rolls of paper (@) arranged on a grid.

The forklifts can only access a roll of paper if there are **fewer than four rolls of paper** in the eight adjacent positions (including diagonals).

---

## Part 1

**Goal:** Count how many rolls of paper can be accessed by a forklift.

### Example

Given:
```
..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
```

Accessible rolls (marked with x):
```
..xx.xx@x.
x@@.@.@.@@
@@@@@.x.@@
@.@@@@..@.
x@.@@@@.@x
.@@@@@@@.@
.@.@.@.@@@
x.@@@.@@@@
.@@@@@@@@.
x.x.@@@.x.
```

**Answer: 13** accessible rolls.

### Approach

For each roll of paper (@):
1. Check all 8 adjacent positions (up, down, left, right, and 4 diagonals)
2. Count how many of those positions contain a roll (@)
3. If the count is **less than 4**, the roll is accessible
4. Sum the total number of accessible rolls

---

## Part 2

**Goal:** Iteratively remove accessible rolls until no more can be removed. Count total rolls removed.

### Key Difference

Once a roll is removed, other rolls may become accessible. Keep removing rolls until no more can be accessed.

### Example

Starting with the same grid, the process removes rolls in waves:
- **Round 1:** Remove 13 accessible rolls
- **Round 2:** Remove 12 rolls (newly accessible after round 1)
- **Round 3:** Remove 7 rolls
- **Round 4:** Remove 5 rolls
- **Round 5:** Remove 2 rolls
- **Round 6:** Remove 1 roll
- **Round 7:** Remove 1 roll
- **Round 8:** Remove 1 roll
- **Round 9:** Remove 1 roll

**Total: 43** rolls removed.

### Approach

1. Find all currently accessible rolls (adjacent roll count < 4)
2. Remove all accessible rolls simultaneously
3. Repeat until no more rolls can be removed
4. Count the total number of rolls removed

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day4/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Compile Part 2
cd Day4/part2 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 (default input)
./Day4/part1/solution

# Run Part 1 with example
./Day4/part1/solution Day4/example.txt

# Run Part 2 (default input)
./Day4/part2/solution

# Run Part 2 with example
./Day4/part2/solution Day4/example.txt
```

## Structure

```
Day4/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution
```

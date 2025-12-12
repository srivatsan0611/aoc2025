# Day 12: Christmas Tree Farm

[Problem Link](https://adventofcode.com/2025/day/12)

## Problem Statement

Given 6 different polyomino shapes and multiple rectangular regions with specified quantities of each shape, determine how many regions can be completely tiled using the given shapes.

---

## Solution

**Goal:** Count regions that can be perfectly tiled with the given polyomino shapes.

### Example

```
4x4: 0 0 0 0 2 0
12x5: 1 0 1 0 2 2
12x5: 1 0 1 0 3 2
```

The first line defines 6 shapes (shapes 0-5), and subsequent lines specify regions with dimensions and the count of each shape to use.

### Approach

This is a backtracking puzzle-solver that:
1. Parses 6 polyomino shapes from the input
2. Precomputes all rotations and reflections for each shape
3. For each region specification:
   - Performs quick area check (total shape area must equal region area)
   - Uses backtracking to attempt placement of all shapes
   - Tries all positions and orientations for each shape
4. Counts regions that can be successfully tiled

The solver uses pruning optimizations and tries shapes in order to reduce the search space.

---

## Running the Code

**From project root:**

```bash
# Compile
cd Day12 && g++ -o solution solution.cpp -std=c++17 -O2 && cd ..

# Run
./Day12/solution Day12/input.txt

# Run with example
./Day12/solution Day12/example.txt
```

## Structure

```
Day12/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
└── solution.cpp     # Solution
```


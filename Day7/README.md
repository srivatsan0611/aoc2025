# Day 7: Laboratories - Tachyon Manifold Beam Splitting

[Problem Link](https://adventofcode.com/2025/day/7)

## Problem Statement

The laboratories contain a tachyon beam splitting system. A tachyon beam starts at position 'S' and moves downward through a grid. When the beam encounters a splitter '^', it stops and creates two new beams that are emitted from the positions immediately to the left and right of the splitter, continuing downward.

Key rules:
1. Tachyon beams always move downward
2. Beams pass freely through empty space '.'
3. When a beam hits a splitter '^', it stops and creates two new beams (one left, one right)
4. Multiple beams can occupy the same position (they merge)
5. Count the total number of splitters that are hit (each splitter counts once even if multiple beams hit it)

---

## Part 1

**Goal:** Count the total number of beam splits that occur.

### Example

Given:
```
.......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............
```

The beam starts at 'S' and moves downward, hitting various splitters and creating a cascade of new beams. Each time a splitter '^' is hit, it creates two new beams that continue downward from the adjacent positions.

**Example Answer: 21** splits.
**Actual Answer: 1573** splits.

### Summary

So this problem was about simulating tachyon beams that split when hitting splitters in a grid. We solved it using BFS to track beam positions and a set to count unique splitters hit - basically the grid traversal with state tracking pattern you'd see on LeetCode.

### Approach

1. Parse the grid and locate the starting position 'S'
2. Use BFS to simulate beam movement:
   - Each beam moves downward from its current position
   - When a beam hits a splitter '^', record that splitter
   - Create two new beams at the positions immediately left and right of the splitter
   - Continue until all beams have either hit a splitter or exited the grid
3. Track which splitters have been hit (using a set to avoid double-counting)
4. Track which beam positions have been processed to avoid infinite loops
5. Return the count of unique splitters hit

**Key Details:**
- Multiple beams can hit the same splitter, but it only counts once
- Beams spawn at the positions adjacent to (not at) the splitter
- Use BFS to process all beams level by level
- Prevent duplicate processing with a visited set

---

## Part 2

**Goal:** Count the total number of unique timelines (paths) a single tachyon particle can take through the manifold.

### The Many-Worlds Interpretation

In Part 2, the physics changes: instead of multiple separate beams, we have a single tachyon particle that exists in a quantum superposition. When it hits a splitter, it takes BOTH paths simultaneously, creating different timeline branches.

Key differences from Part 1:
- Part 1: Count how many splitters were hit (21)
- Part 2: Count how many unique complete paths exist through the manifold (40)

### Example

Using the same grid:
```
.......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............
```

The particle starts at 'S'. Each time it encounters a splitter '^', the timeline branches:
- In one timeline, the particle went left
- In another timeline, the particle went right

**Example Answer: 40** unique timelines.
**Actual Answer: 15093663987272** unique timelines.

### Approach

1. Parse the grid and locate the starting position 'S'
2. Use recursive path counting with memoization:
   - From each position (row, col), count all possible paths to the bottom
   - When hitting a splitter, the path count = paths from left + paths from right
   - When reaching the bottom row without hitting a splitter, count as 1 path
   - Use memoization to cache results and avoid recomputation
3. Return the total count of unique paths from the starting position

**Key Details:**
- This is essentially counting all paths in a tree structure
- Each splitter creates a branching point in the timeline
- Use dynamic programming (memoization) for efficiency
- The answer grows exponentially with the depth of the manifold

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day7/part1 && g++ -o solution solution.cpp -std=c++17 && cd ../..

# Run Part 1 (default input)
./Day7/part1/solution

# Run Part 1 with example
./Day7/part1/solution Day7/example.txt

# Compile Part 2
cd Day7/part2 && g++ -o solution solution.cpp -std=c++17 && cd ../..

# Run Part 2 (default input)
./Day7/part2/solution

# Run Part 2 with example
./Day7/part2/solution Day7/example.txt
```

## Structure

```
Day7/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution
```

# Day 8: Playground

[Problem Link](https://adventofcode.com/2025/day/8)

## Problem Statement

The Elves have a playground with junction boxes positioned in 3D space. Each junction box has X, Y, and Z coordinates. We need to connect junction boxes to form circuits.

---

## Part 1

**Goal:** Connect the 1000 pairs of junction boxes that are closest together (by Euclidean distance), then find the product of the three largest circuit sizes.

### Example

Given 20 junction boxes:
```
162,817,812
57,618,57
906,360,560
... (20 boxes total)
```

After making 10 connections (scaled down from 1000), the circuit sizes are: [5, 4, 2, 2, 1, 1, 1, 1, 1, 1, 1]

**Example Answer: 40** (5 × 4 × 2)

### Summary

So this problem was about finding the closest pairs of 3D points and grouping them into connected components. We solved it using Union-Find to efficiently track which junction boxes belong to the same circuit - basically the disjoint set union pattern you'd see on LeetCode for grouping problems.

### Approach

1. Parse all junction box positions (X, Y, Z coordinates)
2. Calculate all pairwise Euclidean distances: sqrt((x2-x1)² + (y2-y1)² + (z2-z1)²)
3. Sort all pairs by distance (ascending)
4. Use Union-Find to connect the closest pairs:
   - For each pair in sorted order, if they're not already in the same circuit, connect them
   - Stop after making 1000 connections
5. Count the size of each circuit
6. Return the product of the three largest circuit sizes

**Key Details:**
- Use Union-Find (Disjoint Set Union) data structure for efficient circuit tracking
- Distance formula: sqrt((x2-x1)² + (y2-y1)² + (z2-z1)²)
- We need exactly 1000 connections (not 1000 pairs attempted)
- For the example with 20 boxes, we make 10 connections instead of 1000

---

## Part 2

**Goal:** Continue making connections until all junction boxes are in a single circuit. Count the total number of connections made.

### Example

Using the same 20 junction boxes:
```
162,817,812
57,618,57
906,360,560
... (20 boxes total)
```

After making connections until all boxes are in one circuit, the total number of connections is **19** (which makes sense: n-1 edges to connect n nodes).

**Example Answer: 19** connections

### Summary

So this problem was about continuing to connect pairs until we achieve a single connected component - measuring when the graph becomes fully connected. We solved it using Union-Find while counting connections until all components merge into one - basically the minimum spanning tree / graph connectivity pattern you'd see on LeetCode.

### Approach

1. Parse all junction box positions (X, Y, Z coordinates)
2. Calculate all pairwise Euclidean distances: sqrt((x2-x1)² + (y2-y1)² + (z2-z1)²)
3. Sort all pairs by distance (ascending)
4. Use Union-Find to connect pairs:
   - For each pair in sorted order, if they're not already in the same circuit, connect them
   - Continue until all boxes are in a single circuit (when we have n-1 connections for n boxes, or when the root count is 1)
5. Return the total number of connections made

**Key Details:**
- We continue making connections until only 1 circuit remains
- For n junction boxes, we need exactly n-1 connections to form a single circuit
- The answer is much larger than 1000 from Part 1
- This is essentially building a minimum spanning tree

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day8/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 (default input)
./Day8/part1/solution

# Run Part 1 with example
./Day8/part1/solution Day8/example.txt

# Compile Part 2
cd Day8/part2 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 2 (default input)
./Day8/part2/solution

# Run Part 2 with example
./Day8/part2/solution Day8/example.txt
```

## Structure

```
Day8/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution
```

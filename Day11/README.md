# Day 11: Reactor

[Problem Link](https://adventofcode.com/2025/day/11)

## Problem Statement

The problem involves analyzing a directed graph representing a reactor's device connections. Each device has outputs that connect to other devices, and data flows only forward through these connections.

The input format consists of lines where:
- Each line shows a device name followed by a colon and the devices its outputs connect to
- Data flows only forward (no backwards flow through outputs)
- We need to find paths from a device labeled "you" to a device labeled "out"

---

## Part 1

**Goal:** Count the number of different paths from "you" to "out".

### Example

Given:
```
aaa: you hhh
you: bbb ccc
bbb: ddd eee
ccc: ddd eee fff
ddd: ggg
eee: out
fff: out
ggg: out
hhh: ccc fff iii
iii: out
```

The 5 different paths from "you" to "out" are:
1. you → bbb → ddd → ggg → out
2. you → bbb → eee → out
3. you → ccc → ddd → ggg → out
4. you → ccc → eee → out
5. you → ccc → fff → out

**Answer: 5** different paths.

### Approach

1. Parse the input to build a directed graph (adjacency list)
   - Each device maps to a list of devices it connects to
2. Use DFS (Depth-First Search) to explore all possible paths from "you" to "out"
3. Count each complete path that reaches "out"
4. Handle cycles by tracking visited nodes in the current path

**Key Details:**
- This is a path counting problem in a directed graph
- Use DFS with backtracking to explore all paths
- Need to avoid infinite loops by tracking current path

---

## Part 2

**Goal:** Count paths from "svr" to "out" that visit both "dac" AND "fft" (in any order).

### Example

Given:
```
svr: aaa bbb
aaa: fft
fft: ccc
bbb: tty
tty: ccc
ccc: ddd eee
ddd: hub
hub: fff
eee: dac
dac: fff
fff: ggg hhh
ggg: out
hhh: out
```

There are 8 total paths from "svr" to "out", but only **2** visit both "dac" and "fft":
1. svr → aaa → fft → ccc → eee → dac → fff → ggg → out
2. svr → aaa → fft → ccc → eee → dac → fff → hhh → out

**Answer: 2** paths that visit both required nodes.

### Approach

1. Parse the input to build a directed graph (adjacency list)
2. Use Dynamic Programming with memoization
3. State: (current_node, has_visited_dac, has_visited_fft)
4. For each state, compute the number of paths to "out"
5. Only count paths where both flags are true when reaching "out"

**Key Optimization:**
- Instead of tracking all visited nodes (exponential states), only track whether we've seen "dac" and "fft"
- Memoize results for each unique state to avoid recomputation
- This reduces the state space from exponential to O(nodes × 2 × 2)
- With ~600 nodes, this is only ~2400 states to compute

**Performance:**
- Initial DFS with visited tracking: Too slow (exponential paths)
- DP with memoization: ~0.008 seconds

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day11/part1 && g++ -o solution solution.cpp -std=c++17 -O2 && cd ../..

# Run Part 1 (default input)
./Day11/part1/solution Day11/input.txt

# Run Part 1 with example
./Day11/part1/solution Day11/example.txt

# Compile Part 2
cd Day11/part2 && g++ -o solution solution.cpp -std=c++17 -O3 && cd ../..

# Run Part 2 (default input)
./Day11/part2/solution Day11/input.txt

# Run Part 2 with example
./Day11/part2/solution Day11/example2.txt
```

## Structure

```
Day11/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Part 1 example input
├── example2.txt     # Part 2 example input
├── part1/
│   └── solution.cpp # Part 1 solution (DFS path counting)
└── part2/
    └── solution.cpp # Part 2 solution (DP with memoization)
```

## Solutions Summary

| Part | Answer | Approach | Runtime |
|------|--------|----------|---------|
| Part 1 | 472 | DFS with cycle detection | Fast |
| Part 2 | 526811953334940 | DP with memoization | 0.008s |

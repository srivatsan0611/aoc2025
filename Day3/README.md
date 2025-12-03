# Day 3: Lobby

[Problem Link](https://adventofcode.com/2025/day/3)

## Problem Statement

You descend into a vast lobby to find the escalator offline. There are batteries nearby with joltage ratings (1-9) that can power it. The batteries are arranged into banks; each line of digits represents a single bank.

Within each bank, you need to **turn on exactly two batteries**. The joltage produced is the number formed by the digits at the positions of the batteries you've turned on. You cannot rearrange the batteries - if you select positions `i` and `j` where `i < j`, the joltage is `digit[i]` followed by `digit[j]`.

---

## Part 1

**Goal:** Find the maximum joltage possible from each bank and sum them all.

### Example

Given:
```
987654321111111
811111111111119
234234234234278
818181911112111
```

**Breakdown:**
- `987654321111111`: Select positions 0,1 → `98` (maximum possible)
- `811111111111119`: Select positions 0,14 → `89` (maximum possible)
- `234234234234278`: Select positions 12,13 → `78` (maximum possible)
- `818181911112111`: Select positions 6,11 → `92` (maximum possible)

**Total: 98 + 89 + 78 + 92 = 357**

### Approach

For each bank (line):
1. Try all pairs of positions (i, j) where i < j
2. Calculate joltage = digit[i] * 10 + digit[j]
3. Track the maximum joltage
4. Sum all maximum joltages across all banks

**Answer:** `16854` ⭐

---

## Part 2

**Goal:** Find the largest 12-digit joltage possible from each bank and sum them all.

### Key Difference

Instead of selecting 2 batteries, now you must select exactly **12 batteries** to form a 12-digit number, maintaining their original order in the bank.

### Example

Given the same input:
```
987654321111111
811111111111119
234234234234278
818181911112111
```

**Breakdown:**
- `987654321111111`: Select to produce `987654321111` (12 digits)
- `811111111111119`: Select to produce `811111111119` (12 digits)
- `234234234234278`: Select to produce `434234234278` (12 digits)
- `818181911112111`: Select to produce `888911112111` (12 digits)

**Total: 987654321111 + 811111111119 + 434234234278 + 888911112111 = 3121910778619**

### Approach

For each bank (line):
1. Use a **greedy selection strategy**: at each position in the 12-digit output, pick the largest available digit
2. Ensure we can always complete 12 selections by checking that enough positions remain
3. For output position `k`, we need at least `12 - k - 1` remaining positions after selection
4. Search for the largest digit in the valid range and advance past it
5. Convert the resulting 12-digit string to a long long and accumulate

**Answer:** `167526011932478` ⭐

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day3/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Compile Part 2
cd Day3/part2 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 (default input)
./Day3/part1/solution

# Run Part 1 with example
./Day3/part1/solution Day3/example.txt

# Run Part 2 (default input)
./Day3/part2/solution

# Run Part 2 with example
./Day3/part2/solution Day3/example.txt
```

## Structure

```
Day3/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution (coming soon)
```

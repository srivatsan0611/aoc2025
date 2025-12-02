# Day 1: Secret Entrance

[Problem Link](https://adventofcode.com/2025/day/1)

## Problem Statement

You need to open a safe with a dial that displays numbers 0-99. The dial starts at **50**, and you must follow a sequence of rotation instructions to determine the password.

**Rotation Instructions:**
- Format: Letter (L or R) followed by a distance number
- `L` = rotate left (toward lower numbers)
- `R` = rotate right (toward higher numbers)
- The dial wraps around (left from 0 goes to 99; right from 99 goes to 0)

---

## Part 1

**Goal:** Count how many times the dial **lands on 0** after completing a rotation.

### Example

Given: `L68, L30, R48, L5, R60, L55, L1, L99, R14, L82`

```
Start: 50
L68 → 82
L30 → 52
R48 → 0   ✓ (count: 1)
L5  → 95
R60 → 55
L55 → 0   ✓ (count: 2)
L1  → 99
L99 → 0   ✓ (count: 3)
R14 → 14
L82 → 32
```

**Example Answer: 3**

### Approach

Simple simulation with modular arithmetic:
1. Start at position 50
2. For each rotation, update position using modulo 100
3. Count when final position equals 0

**Answer:** `1172` ⭐

---

## Part 2

**Goal:** Count how many times the dial **passes through 0** during rotations (including mid-rotation crossings).

### Key Difference

- Part 1: Only counts when rotation **ends** at 0
- Part 2: Counts **every time** we pass through 0, even during the rotation

### Example

Same rotations, but now counting all crossings:

```
L68 from 50 → crosses 0 once during rotation (50→...→0→...→82)
L30 from 82 → no crossing
R48 from 52 → lands on 0 (52→...→0)
L5 from 0 → no crossing (starts at 0, doesn't cross)
R60 from 95 → crosses 0 once during rotation
L55 from 55 → lands on 0
L1 from 0 → no crossing (starts at 0)
L99 from 99 → lands on 0
R14 from 0 → no crossing (starts at 0)
L82 from 14 → crosses 0 once during rotation
```

Total: 6 crossings (3 from Part 1 + 3 additional mid-rotation crossings)

**Example Answer: 6**

### Approach

Calculate zero crossings mathematically:

**For LEFT rotation** of distance `d` from position `p`:
- If `p == 0`: `count = d / 100` (only full rotations)
- If `p > 0` and `d >= p`: `count = 1 + (d - p) / 100`
- Otherwise: `count = 0`

**For RIGHT rotation** of distance `d` from position `p`:
- If `p == 0`: `count = d / 100` (only full rotations)
- If `p > 0` and `d >= (100 - p)`: `count = 1 + (d - (100 - p)) / 100`
- Otherwise: `count = 0`

**Answer:** `6932` ⭐

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day1/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Compile Part 2
cd Day1/part2 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 (default input)
./Day1/part1/solution

# Run Part 1 with example
./Day1/part1/solution Day1/example.txt

# Run Part 2 (default input)
./Day1/part2/solution

# Run Part 2 with example
./Day1/part2/solution Day1/example.txt
```

## Structure

```
Day1/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution
```

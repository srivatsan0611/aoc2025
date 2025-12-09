# Day 9: Movie Theater

[Problem Link](https://adventofcode.com/2025/day/9)

## Problem Statement

We have a grid with red tiles at specific coordinates. We need to find the largest rectangle that uses two red tiles as opposite corners.

---

## Part 1

**Goal:** Find the largest rectangle area formed by two red tiles as opposite corners.

### Example

Given red tiles at coordinates:
```
7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
```

The largest rectangle has area **50** (formed between coordinates (2,5) and (11,1)).

### Approach

1. Parse all red tile coordinates from the input file (format: `x,y`)
2. For each pair of red tiles, consider them as opposite corners of a rectangle
3. Calculate the area as: `(|x2 - x1| + 1) * (|y2 - y1| + 1)`
4. Track and return the maximum area found

**Key Details:**
- A valid rectangle must have two distinct points
- The area includes the corner tiles themselves (hence the +1)
- We need to check all possible pairs of red tiles (O(n²) combinations)
- Use `long long` to avoid integer overflow with large coordinates

**Pattern:** This is basically a "maximum area rectangle" problem, similar to those LeetCode problems where you pick two points and maximize some metric. Just brute force all pairs and track the max - simple nested loop vibes.

---

## Part 2

**Goal:** Find the largest rectangle area formed by two red tiles as opposite corners, but now the rectangle can only include red or green tiles.

### The Twist

- Red tiles form a polygon in the order they appear in the input (with wraparound)
- Adjacent red tiles in the list are connected by straight lines of green tiles
- All tiles inside the polygon loop are also green
- Rectangles must now only contain red or green tiles (no tiles outside the polygon)

### Example

Using the same coordinates, the largest valid rectangle has area **24** (much smaller than Part 1's 50 because we're constrained to the polygon).

### Approach

1. Parse red tiles as vertices of a polygon (in input order)
2. For each pair of red tiles as opposite corners:
   - Check if the entire rectangle lies within or on the polygon boundary
   - Use point-in-polygon testing (ray casting algorithm)
   - Sample points within the rectangle to verify containment
3. Track the maximum area of valid rectangles

**Key Details:**
- The polygon edges are axis-aligned (horizontal or vertical lines between consecutive red tiles)
- Need to test if rectangle points are inside the polygon using ray casting
- Sample at a 100x100 grid within each rectangle to ensure full containment
- More restrictive than Part 1, so the answer will be smaller

**Pattern:** This is basically "point in polygon" meets "maximum rectangle" - think of it like those geometric containment problems. You're essentially doing a polygon flood fill check for every potential rectangle. Ray casting algorithm is the classic move here, similar to computer graphics hit detection.

---

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day9/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Compile Part 2
cd Day9/part2 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 (default input)
./Day9/part1/solution

# Run Part 1 with example
./Day9/part1/solution Day9/example.txt

# Run Part 2 (default input)
./Day9/part2/solution

# Run Part 2 with example
./Day9/part2/solution Day9/example.txt
```

## Structure

```
Day9/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution
```

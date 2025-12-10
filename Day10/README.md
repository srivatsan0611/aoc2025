# Day 10: Factory

[Problem Link](https://adventofcode.com/2025/day/10)

## Problem Statement

The factory floor contains machines with indicator lights and control buttons. Each button toggles specific lights (XOR operation). The goal is to configure the lights to match a target state using the minimum number of button presses.

Each machine is described by:
- **Target state**: [indicator light diagram] showing desired on/off configuration
- **Buttons**: (button configurations) showing which lights each button toggles
- **Joltage**: {joltage value} (not used in Part 1)

---

## Part 1

**Goal:** Find the minimum number of button presses needed across all machines to configure their indicator lights to the target state.

### Example

Given machines with their target states and button configurations, solve each machine independently using Gaussian elimination over GF(2) (binary field).

**Expected output: 7** (sum of minimum button presses across all machines)

### Approach

1. Parse each machine line to extract:
   - Target state from [indicator light diagram]
   - Button configurations from (parentheses)
2. For each machine, solve the system of linear equations over GF(2):
   - Create a matrix where each column is a button, each row is a light
   - Use Gaussian elimination to find which buttons to press
   - Count the minimum presses needed
3. Sum the minimum presses across all machines

**Key Details:**
- Light states are binary (0 = off, 1 = on)
- Buttons toggle lights via XOR operation
- Need to solve Ax = b over GF(2) where:
  - A is the button-to-light mapping matrix
  - x is the button press vector
  - b is the target state vector
- Use row reduction to find the minimal solution

---

## Part 2

**Goal:** Find the minimum number of button presses needed across all machines to reach their required **joltage counter targets**.

### Problem Interpretation

In joltage mode, indicator lights no longer matter.  
Each machine has:

- A list of **counters**, all starting at 0  
- A set of **buttons**, where each press adds **+1** to specific counters  
- A **target joltage vector** in `{ ... }`

Your task is to press buttons until all counters match their target values — using the **fewest total presses**.

Mathematically, each machine is solving:

`A*x = b`


Where:

- `A[i][j] = 1` if button `j` increments counter `i`
- `x[j]` = number of times button j is pressed (must be integer ≥ 0)
- `b[i]` = target value for counter i

This is **integer linear algebra**, not modulo arithmetic like Part 1.

---

### Example

For the example in the puzzle:

- Machine 1 → 10 presses  
- Machine 2 → 12 presses  
- Machine 3 → 11 presses  

Total:

`10 + 12 + 11 = 33`

### Approach

1. **Parse inputs**:
   - Button mappings from `(i,j,k)`
   - Counter targets from `{a,b,c,...}`
2. **Construct matrix A** and vector b
3. **Perform Gaussian elimination** over real numbers (using `long double`) to get RREF:
   - Identify pivot and free variables
4. **Compute safe upper bounds** for each free variable:
   - A button can’t be pressed more than the smallest target value of the counters it affects
5. **Enumerate all feasible free-variable assignments** within these bounds
6. **Back-substitute** pivot values
7. Reject solutions that:
   - Produce non-integer results  
   - Yield negative button counts  
8. Pick the solution with the **minimum total presses**
9. Sum across all machines


### Key Details

- Systems are often **underdetermined**, so multiple solutions exist  
- Enumeration is efficient because **free variable count is small**  
- Upper bounds prevent search explosion  
- RREF ensures correctness  
- All arithmetic is on standard integers, not modulo operations

--- 

## Running the Code

**From project root:**

```bash
# Compile Part 1
cd Day10/part1 && g++ -o solution solution.cpp -std=c++11 && cd ../..

# Run Part 1 with example
./Day10/part1/solution Day10/example.txt

# Run Part 1 with input
./Day10/part1/solution Day10/input.txt
```

## Structure

```
Day10/
├── README.md        # This file
├── input.txt        # Puzzle input
├── example.txt      # Example input
├── part1/
│   └── solution.cpp # Part 1 solution
└── part2/
    └── solution.cpp # Part 2 solution (TBD)
```

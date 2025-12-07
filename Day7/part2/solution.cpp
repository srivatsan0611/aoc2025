#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Memoization map to cache results for (row, col) -> number of paths
map<pair<int, int>, long long> memo;

// Recursive function to count all paths from (row, col) going downward
long long countPaths(const vector<string>& grid, int row, int col, int rows, int cols) {
    // Base case: if we're out of bounds
    if (col < 0 || col >= cols) {
        return 0;
    }

    // Base case: if we've reached the bottom row
    if (row == rows - 1) {
        return 1; // One complete path
    }

    // Check if we've already computed this
    pair<int, int> state = {row, col};
    if (memo.find(state) != memo.end()) {
        return memo[state];
    }

    long long totalPaths = 0;

    // Move downward from current position
    for (int r = row + 1; r < rows; r++) {
        if (grid[r][col] == '^') {
            // Hit a splitter! The path branches into two timelines
            // Left timeline
            int leftCol = col - 1;
            if (leftCol >= 0) {
                totalPaths += countPaths(grid, r, leftCol, rows, cols);
            }

            // Right timeline
            int rightCol = col + 1;
            if (rightCol < cols) {
                totalPaths += countPaths(grid, r, rightCol, rows, cols);
            }

            // This path stops here (it has split into two new paths)
            break;
        }

        // If we're on the last row without hitting a splitter, count it as one path
        if (r == rows - 1) {
            totalPaths = 1;
        }
    }

    memo[state] = totalPaths;
    return totalPaths;
}

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day7/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Read the grid
    vector<string> grid;
    string line;
    while (getline(input, line)) {
        grid.push_back(line);
    }
    input.close();

    if (grid.empty()) {
        cout << 0 << endl;
        return 0;
    }

    int rows = grid.size();
    int cols = grid[0].size();

    // Find the starting position 'S'
    int startRow = -1, startCol = -1;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'S') {
                startRow = r;
                startCol = c;
                break;
            }
        }
        if (startRow != -1) break;
    }

    if (startRow == -1) {
        cout << 0 << endl;
        return 0;
    }

    // Count all possible paths (timelines) from the starting position
    long long totalTimelines = countPaths(grid, startRow, startCol, rows, cols);

    cout << totalTimelines << endl;

    return 0;
}

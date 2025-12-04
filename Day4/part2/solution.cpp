#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Count adjacent rolls for a position
int countAdjacentRolls(const vector<string>& grid, int i, int j) {
    int rows = grid.size();
    int cols = grid[0].length();

    // Direction vectors for 8 adjacent positions
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int adjacentRolls = 0;

    for (int d = 0; d < 8; d++) {
        int ni = i + dx[d];
        int nj = j + dy[d];

        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
            if (grid[ni][nj] == '@') {
                adjacentRolls++;
            }
        }
    }

    return adjacentRolls;
}

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day4/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Read the grid
    vector<string> grid;
    string line;
    while (getline(input, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    input.close();

    if (grid.empty()) {
        cerr << "Error: Empty grid" << endl;
        return 1;
    }

    int rows = grid.size();
    int cols = grid[0].length();
    int totalRemoved = 0;

    // Keep removing accessible rolls until no more can be removed
    bool changed = true;
    while (changed) {
        changed = false;
        vector<pair<int, int>> toRemove;

        // Find all accessible rolls in current state
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '@') {
                    int adjacentRolls = countAdjacentRolls(grid, i, j);

                    // Forklift can access if fewer than 4 adjacent rolls
                    if (adjacentRolls < 4) {
                        toRemove.push_back({i, j});
                    }
                }
            }
        }

        // Remove all accessible rolls
        if (!toRemove.empty()) {
            changed = true;
            for (const auto& pos : toRemove) {
                grid[pos.first][pos.second] = '.';
                totalRemoved++;
            }
        }
    }

    cout << "Total rolls removed: " << totalRemoved << endl;

    return 0;
}

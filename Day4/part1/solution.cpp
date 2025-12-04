#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

    // Direction vectors for 8 adjacent positions
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int accessibleCount = 0;

    // Check each position in the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Only check positions with rolls of paper
            if (grid[i][j] == '@') {
                int adjacentRolls = 0;

                // Check all 8 adjacent positions
                for (int d = 0; d < 8; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    // Check if position is within bounds
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        if (grid[ni][nj] == '@') {
                            adjacentRolls++;
                        }
                    }
                }

                // Forklift can access if fewer than 4 adjacent rolls
                if (adjacentRolls < 4) {
                    accessibleCount++;
                }
            }
        }
    }

    cout << "Accessible rolls: " << accessibleCount << endl;

    return 0;
}

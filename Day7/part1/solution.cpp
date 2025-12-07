#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Beam {
    int row;
    int col;
};

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

    // Simulate beams using BFS
    queue<Beam> beamQueue;
    beamQueue.push({startRow, startCol});

    // Track which splitters have been hit (to count each splitter only once)
    set<pair<int, int>> hitSplitters;

    // Track which beams we've already processed to avoid infinite loops
    set<pair<int, int>> processedBeams;

    while (!beamQueue.empty()) {
        Beam current = beamQueue.front();
        beamQueue.pop();

        // Move downward from current position
        for (int r = current.row + 1; r < rows; r++) {
            int c = current.col;

            if (grid[r][c] == '^') {
                // Hit a splitter! Count this split if we haven't hit this splitter before
                if (hitSplitters.find({r, c}) == hitSplitters.end()) {
                    hitSplitters.insert({r, c});
                }

                // Create two new beams: one to the left and one to the right
                int leftCol = c - 1;
                int rightCol = c + 1;

                // Add left beam if valid and not already processed
                if (leftCol >= 0 && processedBeams.find({r, leftCol}) == processedBeams.end()) {
                    beamQueue.push({r, leftCol});
                    processedBeams.insert({r, leftCol});
                }

                // Add right beam if valid and not already processed
                if (rightCol < cols && processedBeams.find({r, rightCol}) == processedBeams.end()) {
                    beamQueue.push({r, rightCol});
                    processedBeams.insert({r, rightCol});
                }

                // This beam stops here
                break;
            }
        }
    }

    int splitCount = hitSplitters.size();

    cout << splitCount << endl;

    return 0;
}

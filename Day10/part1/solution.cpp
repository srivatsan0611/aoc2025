#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Parse the target state from [.##.] format
vector<int> parseTargetState(const string& line) {
    vector<int> target;
    size_t start = line.find('[');
    size_t end = line.find(']');

    if (start != string::npos && end != string::npos) {
        string lights = line.substr(start + 1, end - start - 1);
        for (char c : lights) {
            target.push_back(c == '#' ? 1 : 0);
        }
    }

    return target;
}

// Parse button configurations from (1,3) format
vector<vector<int>> parseButtons(const string& line) {
    vector<vector<int>> buttons;
    size_t pos = 0;

    while ((pos = line.find('(', pos)) != string::npos) {
        size_t end = line.find(')', pos);
        if (end == string::npos) break;

        string buttonStr = line.substr(pos + 1, end - pos - 1);
        vector<int> button;

        if (!buttonStr.empty()) {
            stringstream ss(buttonStr);
            string num;
            while (getline(ss, num, ',')) {
                button.push_back(stoi(num));
            }
        }

        buttons.push_back(button);
        pos = end + 1;
    }

    return buttons;
}

// Solve the system using Gaussian elimination over GF(2)
int solveGF2(vector<vector<int>>& matrix, vector<int>& target) {
    int rows = matrix.size();
    if (rows == 0) return 0;

    int cols = matrix[0].size();
    if (cols == 0) return 0;

    // Create augmented matrix [A | b]
    vector<vector<int>> aug(rows, vector<int>(cols + 1));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            aug[i][j] = matrix[i][j];
        }
        aug[i][cols] = target[i];
    }

    // Track which columns have pivots
    vector<int> pivot_col(rows, -1);
    vector<bool> is_pivot(cols, false);

    // Gaussian elimination to RREF (Reduced Row Echelon Form)
    int pivot_row = 0;
    for (int col = 0; col < cols && pivot_row < rows; col++) {
        // Find pivot
        int pivot = -1;
        for (int row = pivot_row; row < rows; row++) {
            if (aug[row][col] == 1) {
                pivot = row;
                break;
            }
        }

        if (pivot == -1) continue;

        // Swap rows
        if (pivot != pivot_row) {
            swap(aug[pivot], aug[pivot_row]);
        }

        pivot_col[pivot_row] = col;
        is_pivot[col] = true;

        // Eliminate all other rows (not just below)
        for (int row = 0; row < rows; row++) {
            if (row != pivot_row && aug[row][col] == 1) {
                for (int j = 0; j <= cols; j++) {
                    aug[row][j] ^= aug[pivot_row][j];
                }
            }
        }

        pivot_row++;
    }

    // Check for inconsistency
    for (int i = pivot_row; i < rows; i++) {
        if (aug[i][cols] == 1) {
            // No solution exists
            return -1;
        }
    }

    // Find free variables
    vector<int> free_vars;
    for (int i = 0; i < cols; i++) {
        if (!is_pivot[i]) {
            free_vars.push_back(i);
        }
    }

    // Try all combinations of free variables to find minimum
    int min_presses = cols + 1;
    int num_free = free_vars.size();
    int num_combinations = (1 << num_free);

    for (int mask = 0; mask < num_combinations; mask++) {
        vector<int> solution(cols, 0);

        // Set free variables according to mask
        for (int i = 0; i < num_free; i++) {
            solution[free_vars[i]] = (mask >> i) & 1;
        }

        // Solve for pivot variables
        for (int i = 0; i < pivot_row; i++) {
            if (pivot_col[i] != -1) {
                int val = aug[i][cols];
                for (int j = 0; j < cols; j++) {
                    if (j != pivot_col[i] && aug[i][j] == 1) {
                        val ^= solution[j];
                    }
                }
                solution[pivot_col[i]] = val;
            }
        }

        // Count button presses
        int count = 0;
        for (int val : solution) {
            count += val;
        }

        min_presses = min(min_presses, count);
    }

    return min_presses;
}

// Solve a single machine
int solveMachine(const string& line) {
    vector<int> target = parseTargetState(line);
    vector<vector<int>> buttons = parseButtons(line);

    if (target.empty() || buttons.empty()) return 0;

    int numLights = target.size();
    int numButtons = buttons.size();

    // Create matrix: rows = lights, cols = buttons
    vector<vector<int>> matrix(numLights, vector<int>(numButtons, 0));

    for (int j = 0; j < numButtons; j++) {
        for (int lightIdx : buttons[j]) {
            if (lightIdx >= 0 && lightIdx < numLights) {
                matrix[lightIdx][j] = 1;
            }
        }
    }

    return solveGF2(matrix, target);
}

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : "Day10/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    string line;
    int totalPresses = 0;

    while (getline(input, line)) {
        if (line.empty()) continue;

        int presses = solveMachine(line);
        if (presses == -1) {
            cerr << "No solution found for machine" << endl;
            continue;
        }
        totalPresses += presses;
    }

    input.close();

    cout << totalPresses << endl;

    return 0;
}

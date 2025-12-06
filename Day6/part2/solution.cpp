#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day6/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Read all lines
    vector<string> lines;
    string line;
    while (getline(input, line)) {
        lines.push_back(line);
    }
    input.close();

    if (lines.empty()) {
        cout << 0 << endl;
        return 0;
    }

    // Find the maximum line length to handle all columns
    size_t maxLen = 0;
    for (const auto& l : lines) {
        maxLen = max(maxLen, l.length());
    }

    // Pad all lines to the same length for easier column processing
    for (auto& l : lines) {
        while (l.length() < maxLen) {
            l += ' ';
        }
    }

    // Extract operation symbols from the last row
    string opRow = lines[lines.size() - 1];

    // Parse columns from right to left
    // For each column, read the vertical number (top to bottom = most to least significant)
    vector<long long> columnNumbers;
    vector<char> columnOps;

    for (int col = maxLen - 1; col >= 0; col--) {
        // Check if this column is all spaces (separator) or has content
        bool hasContent = false;
        for (size_t row = 0; row < lines.size() - 1; row++) {
            if (col < (int)lines[row].length() && lines[row][col] != ' ') {
                hasContent = true;
                break;
            }
        }

        // Check if operation row has an operator at this column
        char op = ' ';
        if (col < (int)opRow.length()) {
            if (opRow[col] == '*' || opRow[col] == '+') {
                op = opRow[col];
            }
        }

        if (hasContent) {
            // Build the number from this column (top to bottom)
            string numStr = "";
            for (size_t row = 0; row < lines.size() - 1; row++) {
                if (col < (int)lines[row].length() && lines[row][col] != ' ') {
                    numStr += lines[row][col];
                }
            }

            if (!numStr.empty()) {
                long long num = stoll(numStr);
                columnNumbers.push_back(num);
                columnOps.push_back(op);
            }
        }
    }

    // Now group columns into problems
    // A problem ends when we see an operator
    vector<vector<long long>> problems;
    vector<char> problemOps;
    vector<long long> currentProblem;

    for (size_t i = 0; i < columnNumbers.size(); i++) {
        currentProblem.push_back(columnNumbers[i]);

        // If this column has an operator, it marks the end of a problem
        if (columnOps[i] == '*' || columnOps[i] == '+') {
            problems.push_back(currentProblem);
            problemOps.push_back(columnOps[i]);
            currentProblem.clear();
        }
    }

    // Calculate result for each problem
    long long grandTotal = 0;

    for (size_t i = 0; i < problems.size(); i++) {
        const auto& nums = problems[i];
        char op = problemOps[i];

        if (nums.empty()) continue;

        long long result = nums[0];
        for (size_t j = 1; j < nums.size(); j++) {
            if (op == '*') {
                result *= nums[j];
            } else {
                result += nums[j];
            }
        }

        grandTotal += result;
    }

    cout << grandTotal << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

    // Parse each row to extract numbers
    vector<vector<long long>> rows;
    for (size_t i = 0; i < lines.size() - 1; i++) {  // Skip last line (operations)
        vector<long long> rowNumbers;
        stringstream ss(lines[i]);
        long long num;
        while (ss >> num) {
            rowNumbers.push_back(num);
        }
        rows.push_back(rowNumbers);
    }

    // Parse operations from last line
    vector<char> operations;
    for (char c : lines[lines.size() - 1]) {
        if (c == '*' || c == '+') {
            operations.push_back(c);
        }
    }

    // Now we have rows of numbers and operations
    // Each column represents a problem
    // Determine number of problems (columns)
    size_t numProblems = operations.size();

    // Calculate result for each problem
    long long grandTotal = 0;

    for (size_t prob = 0; prob < numProblems; prob++) {
        // Collect all numbers in this column
        vector<long long> numbers;
        for (size_t row = 0; row < rows.size(); row++) {
            if (prob < rows[row].size()) {
                numbers.push_back(rows[row][prob]);
            }
        }

        if (numbers.empty()) continue;

        // Apply the operation
        char op = operations[prob];
        long long result = numbers[0];
        for (size_t i = 1; i < numbers.size(); i++) {
            if (op == '*') {
                result *= numbers[i];
            } else {
                result += numbers[i];
            }
        }

        grandTotal += result;
    }

    cout << grandTotal << endl;

    return 0;
}

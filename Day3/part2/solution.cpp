#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day3/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    long long totalJoltage = 0;

    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;

        // Select exactly 12 batteries to form the largest 12-digit number
        // Use greedy approach: at each output position, pick the largest digit
        // that still leaves enough remaining digits to complete 12 total

        string result = "";
        int startPos = 0;

        for (int outputPos = 0; outputPos < 12; outputPos++) {
            // How many more digits do we need to select after this one?
            int remaining = 12 - outputPos - 1;

            // How many positions are left in the input after we make a selection?
            int positionsLeft = line.length() - startPos;

            // We must leave at least 'remaining' positions for future selections
            // So the latest we can pick from is: line.length() - remaining - 1
            int maxSearchPos = line.length() - remaining - 1;

            // Find the largest digit in the range [startPos, maxSearchPos]
            char largestDigit = '0';
            int largestPos = startPos;

            for (int i = startPos; i <= maxSearchPos; i++) {
                if (line[i] > largestDigit) {
                    largestDigit = line[i];
                    largestPos = i;
                }
            }

            result += largestDigit;
            startPos = largestPos + 1;
        }

        // Convert 12-digit string to long long
        long long joltage = stoll(result);
        totalJoltage += joltage;
    }

    input.close();

    cout << "Total output joltage: " << totalJoltage << endl;

    return 0;
}

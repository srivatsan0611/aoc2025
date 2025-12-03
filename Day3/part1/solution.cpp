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

        // Find the maximum joltage by selecting two batteries at positions i < j
        long long maxJoltage = 0;

        for (size_t i = 0; i < line.length(); i++) {
            for (size_t j = i + 1; j < line.length(); j++) {
                long long joltage = (line[i] - '0') * 10 + (line[j] - '0');
                maxJoltage = max(maxJoltage, joltage);
            }
        }

        totalJoltage += maxJoltage;
    }

    input.close();

    cout << "Total output joltage: " << totalJoltage << endl;

    return 0;
}

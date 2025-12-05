#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day5/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Read fresh ID ranges
    vector<pair<long long, long long>> ranges;
    string line;
    bool readingRanges = true;

    while (getline(input, line)) {
        if (line.empty()) {
            // Blank line separates ranges from ingredient IDs
            readingRanges = false;
            continue;
        }

        if (readingRanges) {
            // Parse range: "start-end"
            size_t dashPos = line.find('-');
            if (dashPos != string::npos) {
                long long start = stoll(line.substr(0, dashPos));
                long long end = stoll(line.substr(dashPos + 1));
                ranges.push_back({start, end});
            }
        }
    }
    input.close();

    // Now read ingredient IDs and check if they're fresh
    input.open(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    readingRanges = true;
    int freshCount = 0;

    while (getline(input, line)) {
        if (line.empty()) {
            readingRanges = false;
            continue;
        }

        if (!readingRanges) {
            // Parse ingredient ID
            long long id = stoll(line);
            
            // Check if ID falls into any range
            bool isFresh = false;
            for (const auto& range : ranges) {
                if (id >= range.first && id <= range.second) {
                    isFresh = true;
                    break;
                }
            }

            if (isFresh) {
                freshCount++;
            }
        }
    }
    input.close();

    cout << "Fresh ingredients: " << freshCount << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

    while (getline(input, line)) {
        if (line.empty()) {
            // Blank line - we're done reading ranges
            break;
        }

        // Parse range: "start-end"
        size_t dashPos = line.find('-');
        if (dashPos != string::npos) {
            long long start = stoll(line.substr(0, dashPos));
            long long end = stoll(line.substr(dashPos + 1));
            ranges.push_back({start, end});
        }
    }
    input.close();

    if (ranges.empty()) {
        cerr << "Error: No ranges found" << endl;
        return 1;
    }

    // Sort ranges by start position
    sort(ranges.begin(), ranges.end());

    // Merge overlapping ranges to get total count efficiently
    vector<pair<long long, long long>> merged;
    merged.push_back(ranges[0]);

    for (size_t i = 1; i < ranges.size(); i++) {
        long long currentStart = ranges[i].first;
        long long currentEnd = ranges[i].second;
        long long lastEnd = merged.back().second;

        // Check if current range overlaps or touches the last merged range
        if (currentStart <= lastEnd + 1) {
            // Merge: extend the last range if needed
            merged.back().second = max(lastEnd, currentEnd);
        } else {
            // No overlap, add as new range
            merged.push_back(ranges[i]);
        }
    }

    // Count total IDs in merged ranges
    long long totalFreshIDs = 0;
    for (const auto& range : merged) {
        totalFreshIDs += (range.second - range.first + 1);
    }

    cout << "Total fresh ingredient IDs: " << totalFreshIDs << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool is_invalid_id(long long num) {
    // Check if a number is invalid (made of a sequence repeated twice)
    // E.g., 55 (5+5), 6464 (64+64), 123123 (123+123)
    string s = to_string(num);
    int length = s.length();

    // Must be even length to be repeated twice
    if (length % 2 != 0) {
        return false;
    }

    // Check if first half equals second half
    int mid = length / 2;
    return s.substr(0, mid) == s.substr(mid);
}

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day2/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    string line;
    getline(input, line);
    input.close();

    // Parse the ranges
    vector<pair<long long, long long> > ranges;
    stringstream ss(line);
    string range_str;

    while (getline(ss, range_str, ',')) {
        // Trim whitespace
        size_t start = range_str.find_first_not_of(" \t\n\r");
        if (start == string::npos) continue;
        range_str = range_str.substr(start);

        size_t dash_pos = range_str.find('-');
        // Find the last dash (to handle negative numbers if any, but problem says none)
        size_t last_dash = range_str.rfind('-');

        long long range_start = stoll(range_str.substr(0, last_dash));
        long long range_end = stoll(range_str.substr(last_dash + 1));

        pair<long long, long long> p;
        p.first = range_start;
        p.second = range_end;
        ranges.push_back(p);
    }

    long long total = 0;
    int invalid_count = 0;

    // Check each range for invalid IDs
    for (int i = 0; i < ranges.size(); i++) {
        long long start = ranges[i].first;
        long long end = ranges[i].second;

        for (long long id = start; id <= end; id++) {
            if (is_invalid_id(id)) {
                total += id;
                invalid_count++;
            }
        }
    }

    cout << "Sum of invalid IDs: " << total << endl;

    return 0;
}

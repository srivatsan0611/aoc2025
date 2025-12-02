#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day1/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    int position = 50;  // Starting position
    int count = 0;      // Count of times we cross/land on 0

    string line;
    // Read entire file content
    string content;
    while (getline(input, line)) {
        content += line + ",";
    }
    input.close();

    stringstream ss(content);
    string command;

    // Parse comma-separated or newline-separated commands
    while (getline(ss, command, ',')) {
        // Trim whitespace
        size_t start = command.find_first_not_of(" \t\n\r");
        if (start == string::npos) continue;
        command = command.substr(start);

        if (command.empty()) continue;

        char direction = command[0];
        int distance = stoi(command.substr(1));

        // Count zero crossings during rotation (Part 2)
        if (direction == 'L') {
            // Count how many times we cross 0 going left
            if (position == 0) {
                // Starting at 0, only count full rotations
                count += distance / 100;
            } else {
                // Count if we reach 0 in this rotation
                if (distance >= position) {
                    count += 1 + (distance - position) / 100;
                }
            }

            position = (position - distance) % 100;
            // Handle negative modulo in C++
            if (position < 0) position += 100;
        } else if (direction == 'R') {
            // Count how many times we cross 0 going right
            if (position == 0) {
                // Starting at 0, only count full rotations
                count += distance / 100;
            } else {
                int steps_to_zero = 100 - position;
                if (distance >= steps_to_zero) {
                    count += 1 + (distance - steps_to_zero) / 100;
                }
            }

            position = (position + distance) % 100;
        }
    }

    cout << "Password: " << count << endl;

    return 0;
}

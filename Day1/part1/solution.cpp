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
    int count = 0;      // Count of times we land on 0

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

        // Apply rotation
        if (direction == 'L') {
            position = (position - distance) % 100;
            // Handle negative modulo in C++
            if (position < 0) position += 100;
        } else if (direction == 'R') {
            position = (position + distance) % 100;
        }

        // Check if we landed on 0
        if (position == 0) {
            count++;
        }
    }

    cout << "Password: " << count << endl;

    return 0;
}

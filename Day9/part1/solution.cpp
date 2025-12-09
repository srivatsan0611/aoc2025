#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

// Structure to represent a coordinate
struct Coordinate {
    long long x, y;
};

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day9/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Read all red tile coordinates
    vector<Coordinate> redTiles;
    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;

        // Parse x,y coordinates
        stringstream ss(line);
        string xStr, yStr;
        getline(ss, xStr, ',');
        getline(ss, yStr, ',');

        Coordinate coord;
        coord.x = stoi(xStr);
        coord.y = stoi(yStr);
        redTiles.push_back(coord);
    }
    input.close();

    int n = redTiles.size();
    long long maxArea = 0;

    // Check all pairs of red tiles as opposite corners
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Calculate rectangle area using the two tiles as opposite corners
            // Include the corner tiles themselves in the count
            long long width = abs(redTiles[i].x - redTiles[j].x) + 1;
            long long height = abs(redTiles[i].y - redTiles[j].y) + 1;
            long long area = width * height;

            // Update maximum area
            maxArea = max(maxArea, area);
        }
    }

    cout << maxArea << endl;

    return 0;
}

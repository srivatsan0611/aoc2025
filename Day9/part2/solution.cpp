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

// Check if a point is inside or on the boundary of the polygon using ray casting
bool isInsideOrOnPolygon(const vector<Coordinate>& polygon, long long x, long long y) {
    int n = polygon.size();

    // First, check if the point is on any edge of the polygon
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        long long x1 = polygon[i].x, y1 = polygon[i].y;
        long long x2 = polygon[j].x, y2 = polygon[j].y;

        // Check if point is on the line segment between polygon[i] and polygon[j]
        if (x1 == x2) {
            // Vertical line
            if (x == x1 && min(y1, y2) <= y && y <= max(y1, y2)) {
                return true;
            }
        } else if (y1 == y2) {
            // Horizontal line
            if (y == y1 && min(x1, x2) <= x && x <= max(x1, x2)) {
                return true;
            }
        }
    }

    // Ray casting algorithm to check if point is inside polygon
    bool inside = false;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        long long xi = polygon[i].x, yi = polygon[i].y;
        long long xj = polygon[j].x, yj = polygon[j].y;

        if ((yi > y) != (yj > y) &&
            x < (xj - xi) * (y - yi) / (yj - yi) + xi) {
            inside = !inside;
        }
    }

    return inside;
}

// Check if all corners of a rectangle are inside or on the polygon
bool isRectangleValid(const vector<Coordinate>& polygon, long long x1, long long y1, long long x2, long long y2) {
    long long minX = min(x1, x2);
    long long maxX = max(x1, x2);
    long long minY = min(y1, y2);
    long long maxY = max(y1, y2);

    // Check corners first (quick rejection)
    if (!isInsideOrOnPolygon(polygon, minX, minY)) return false;
    if (!isInsideOrOnPolygon(polygon, maxX, minY)) return false;
    if (!isInsideOrOnPolygon(polygon, minX, maxY)) return false;
    if (!isInsideOrOnPolygon(polygon, maxX, maxY)) return false;

    // Sample points to ensure entire rectangle is inside
    long long width = maxX - minX;
    long long height = maxY - minY;

    // Sample at 100 points in each dimension
    long long stepX = max(1LL, width / 100);
    long long stepY = max(1LL, height / 100);

    for (long long x = minX; x <= maxX; x += stepX) {
        for (long long y = minY; y <= maxY; y += stepY) {
            if (!isInsideOrOnPolygon(polygon, x, y)) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day9/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Read all red tile coordinates (they form a polygon in order)
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
        coord.x = stoll(xStr);
        coord.y = stoll(yStr);
        redTiles.push_back(coord);
    }
    input.close();

    int n = redTiles.size();
    long long maxArea = 0;

    // Check all pairs of red tiles as opposite corners
    // Only consider rectangles where all tiles are inside or on the polygon
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long x1 = redTiles[i].x, y1 = redTiles[i].y;
            long long x2 = redTiles[j].x, y2 = redTiles[j].y;

            // Check if the rectangle is valid (all tiles are red or green)
            if (isRectangleValid(redTiles, x1, y1, x2, y2)) {
                long long width = abs(x1 - x2) + 1;
                long long height = abs(y1 - y2) + 1;
                long long area = width * height;

                maxArea = max(maxArea, area);
            }
        }
    }

    cout << maxArea << endl;

    return 0;
}

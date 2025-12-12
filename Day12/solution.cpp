#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Shape {
    vector<pair<int, int>> cells;

    void normalize() {
        if (cells.empty()) return;
        int minR = cells[0].first, minC = cells[0].second;
        for (auto [r, c] : cells) {
            minR = min(minR, r);
            minC = min(minC, c);
        }
        for (auto &[r, c] : cells) {
            r -= minR;
            c -= minC;
        }
        sort(cells.begin(), cells.end());
    }

    Shape rotate() const {
        Shape s;
        for (auto [r, c] : cells) {
            s.cells.push_back({c, -r});
        }
        s.normalize();
        return s;
    }

    Shape flip() const {
        Shape s;
        for (auto [r, c] : cells) {
            s.cells.push_back({r, -c});
        }
        s.normalize();
        return s;
    }

    bool operator<(const Shape &other) const {
        return cells < other.cells;
    }
};

vector<Shape> getVariants(const Shape &shape) {
    set<Shape> variants;
    Shape s = shape;
    for (int i = 0; i < 4; i++) {
        variants.insert(s);
        variants.insert(s.flip());
        s = s.rotate();
    }
    return vector<Shape>(variants.begin(), variants.end());
}

bool canPlace(const vector<vector<int>> &grid, const Shape &shape, int r, int c, int W, int H) {
    for (auto [dr, dc] : shape.cells) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= H || nc < 0 || nc >= W || grid[nr][nc] != 0) {
            return false;
        }
    }
    return true;
}

void place(vector<vector<int>> &grid, const Shape &shape, int r, int c, int id) {
    for (auto [dr, dc] : shape.cells) {
        grid[r + dr][c + dc] = id;
    }
}

void remove(vector<vector<int>> &grid, const Shape &shape, int r, int c) {
    for (auto [dr, dc] : shape.cells) {
        grid[r + dr][c + dc] = 0;
    }
}

bool solve(vector<vector<int>> &grid, vector<int> &counts,
           const vector<vector<Shape>> &allVariants, int W, int H) {
    // Check if all pieces are placed
    bool allZero = true;
    for (int c : counts) {
        if (c > 0) {
            allZero = false;
            break;
        }
    }
    if (allZero) {
        return true;
    }

    // Pick first shape type that still needs to be placed
    int shapeIdx = -1;
    for (int i = 0; i < 6; i++) {
        if (counts[i] > 0) {
            shapeIdx = i;
            break;
        }
    }

    if (shapeIdx == -1) return false;

    // Try all possible positions for this shape
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            for (const Shape &variant : allVariants[shapeIdx]) {
                if (canPlace(grid, variant, r, c, W, H)) {
                    place(grid, variant, r, c, shapeIdx + 1);
                    counts[shapeIdx]--;

                    if (solve(grid, counts, allVariants, W, H)) {
                        return true;
                    }

                    counts[shapeIdx]++;
                    remove(grid, variant, r, c);
                }
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : "../input.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    // Parse shapes
    vector<Shape> shapes(6);
    string line;

    for (int shapeIdx = 0; shapeIdx < 6; shapeIdx++) {
        getline(file, line); // Skip shape index line
        vector<string> pattern;
        while (getline(file, line) && !line.empty()) {
            pattern.push_back(line);
        }

        for (int r = 0; r < pattern.size(); r++) {
            for (int c = 0; c < pattern[r].size(); c++) {
                if (pattern[r][c] == '#') {
                    shapes[shapeIdx].cells.push_back({r, c});
                }
            }
        }
        shapes[shapeIdx].normalize();
    }

    // Precompute all variants
    vector<vector<Shape>> allVariants(6);
    for (int i = 0; i < 6; i++) {
        allVariants[i] = getVariants(shapes[i]);
    }

    // Process regions
    int validCount = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t colonPos = line.find(':');
        string dimensions = line.substr(0, colonPos);
        size_t xPos = dimensions.find('x');
        int W = stoi(dimensions.substr(0, xPos));
        int H = stoi(dimensions.substr(xPos + 1));

        vector<int> counts(6);
        size_t pos = colonPos + 1;
        for (int i = 0; i < 6; i++) {
            while (pos < line.size() && line[pos] == ' ') pos++;
            size_t endPos = pos;
            while (endPos < line.size() && line[endPos] != ' ') endPos++;
            counts[i] = stoi(line.substr(pos, endPos - pos));
            pos = endPos;
        }

        // Quick area check
        int totalArea = 0;
        for (int i = 0; i < 6; i++) {
            totalArea += counts[i] * shapes[i].cells.size();
        }

        if (totalArea > W * H) {
            continue; // Cannot fit
        }

        // Try to solve
        vector<vector<int>> grid(H, vector<int>(W, 0));
        if (solve(grid, counts, allVariants, W, H)) {
            validCount++;
        }
    }

    file.close();
    cout << validCount << endl;
    return 0;
}

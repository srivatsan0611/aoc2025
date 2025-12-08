#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

// Structure to represent a junction box
struct JunctionBox {
    int x, y, z;
};

// Structure to represent a pair with distance
struct BoxPair {
    int index1, index2;
    double distance;
    
    bool operator<(const BoxPair& other) const {
        return distance < other.distance;
    }
};

// Union-Find data structure
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false; // Already in the same set
        }
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        return true; // Successfully united
    }
};

// Calculate Euclidean distance between two junction boxes
double calculateDistance(const JunctionBox& a, const JunctionBox& b) {
    long long dx = (long long)a.x - b.x;
    long long dy = (long long)a.y - b.y;
    long long dz = (long long)a.z - b.z;
    return sqrt((double)(dx * dx + dy * dy + dz * dz));
}

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day8/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Read all junction boxes
    vector<JunctionBox> boxes;
    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;
        
        // Parse X,Y,Z coordinates
        stringstream ss(line);
        string xStr, yStr, zStr;
        getline(ss, xStr, ',');
        getline(ss, yStr, ',');
        getline(ss, zStr, ',');
        
        JunctionBox box;
        box.x = stoi(xStr);
        box.y = stoi(yStr);
        box.z = stoi(zStr);
        boxes.push_back(box);
    }
    input.close();

    int n = boxes.size();
    
    // Calculate all pairwise distances
    vector<BoxPair> pairs;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            BoxPair pair;
            pair.index1 = i;
            pair.index2 = j;
            pair.distance = calculateDistance(boxes[i], boxes[j]);
            pairs.push_back(pair);
        }
    }
    
    // Sort pairs by distance
    sort(pairs.begin(), pairs.end());
    
    // Determine how many pairs to attempt
    // For example with 20 boxes: 10 pairs
    // For actual input with 1000 boxes: 1000 pairs
    int targetPairs = (n == 20) ? 10 : 1000;

    // Use Union-Find to connect boxes
    UnionFind uf(n);

    for (int i = 0; i < targetPairs && i < (int)pairs.size(); i++) {
        // Try to unite the two boxes (may fail if already connected)
        uf.unite(pairs[i].index1, pairs[i].index2);
    }
    
    // Count circuit sizes
    vector<int> circuitSizes(n, 0);
    for (int i = 0; i < n; i++) {
        int root = uf.find(i);
        circuitSizes[root]++;
    }
    
    // Collect non-zero circuit sizes
    vector<int> sizes;
    for (int i = 0; i < n; i++) {
        if (circuitSizes[i] > 0) {
            sizes.push_back(circuitSizes[i]);
        }
    }
    
    // Sort circuit sizes in descending order
    sort(sizes.begin(), sizes.end(), greater<int>());
    
    // Calculate product of three largest sizes
    long long result = 1;
    for (int i = 0; i < min(3, (int)sizes.size()); i++) {
        result *= sizes[i];
    }
    
    cout << result << endl;

    return 0;
}

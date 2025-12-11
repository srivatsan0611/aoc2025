#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

// Graph represented as adjacency list
unordered_map<string, vector<string>> graph;

// DFS to count all paths from current node to target
int countPaths(const string& current, const string& target) {
    // Base case: reached the target
    if (current == target) {
        return 1;
    }

    // If current node has no outgoing edges, no path exists
    if (graph.find(current) == graph.end()) {
        return 0;
    }

    // Count paths through all neighbors
    int totalPaths = 0;
    for (const string& neighbor : graph[current]) {
        totalPaths += countPaths(neighbor, target);
    }

    return totalPaths;
}

int main(int argc, char* argv[]) {
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "Day11/input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Parse the graph
    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;

        // Parse line format: "node: neighbor1 neighbor2 ..."
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string node = line.substr(0, colonPos);
        string neighborsStr = line.substr(colonPos + 1);

        // Parse neighbors
        istringstream iss(neighborsStr);
        string neighbor;
        vector<string> neighbors;
        while (iss >> neighbor) {
            neighbors.push_back(neighbor);
        }

        graph[node] = neighbors;
    }
    input.close();

    // Count all paths from "you" to "out"
    int pathCount = countPaths("you", "out");

    // Output only the answer
    cout << pathCount << endl;

    return 0;
}

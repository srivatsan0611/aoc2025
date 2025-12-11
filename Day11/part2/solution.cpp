#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <map>
#include <tuple>

using namespace std;

// Graph represented as adjacency list
unordered_map<string, vector<string>> graph;

// DP memoization: state = (node, visitedDac, visitedFft) -> count
map<tuple<string, int, int>, long long> dp;

// Count paths from node to "out" with state (visitedDac, visitedFft)
long long countPaths(const string& node, int hasDac, int hasFft) {
    // Check if we're at target
    if (node == "out") {
        return (hasDac && hasFft) ? 1 : 0;
    }

    // Check memo
    auto key = make_tuple(node, hasDac, hasFft);
    if (dp.count(key)) {
        return dp[key];
    }

    // Update state based on current node
    int newDac = hasDac || (node == "dac" ? 1 : 0);
    int newFft = hasFft || (node == "fft" ? 1 : 0);

    // If no neighbors, return 0
    if (!graph.count(node)) {
        return dp[key] = 0;
    }

    // Sum paths through all neighbors
    long long total = 0;
    for (const string& neighbor : graph[node]) {
        total += countPaths(neighbor, newDac, newFft);
    }

    return dp[key] = total;
}

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : "input.txt";

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    // Parse the graph
    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;

        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string node = line.substr(0, colonPos);
        string neighborsStr = line.substr(colonPos + 1);

        istringstream iss(neighborsStr);
        string neighbor;
        vector<string> neighbors;
        while (iss >> neighbor) {
            neighbors.push_back(neighbor);
        }

        graph[node] = neighbors;
    }
    input.close();

    // Count all paths from "svr" to "out" that visit both "dac" and "fft"
    long long result = countPaths("svr", 0, 0);

    cout << result << endl;

    return 0;
}

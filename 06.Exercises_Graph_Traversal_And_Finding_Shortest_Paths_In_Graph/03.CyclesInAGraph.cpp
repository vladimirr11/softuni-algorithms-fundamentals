#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

constexpr int arrSize = 2;

using Graph = std::map<char, std::vector<char>>;

Graph readInput() {
    Graph inputGraph;

    std::string line;
    while (std::getline(std::cin >> std::ws, line) && line != "End") {
        const char c0 = line[0], c1 = line[2];
        inputGraph[c0].push_back(c1);
    }

    return inputGraph;
}

void dfsToCheckCyclesInGraph(Graph& graph, char node, std::set<char>& visited, std::set<char>& cycleNodes) {
    if (cycleNodes.find(node) != cycleNodes.end()) {
        throw "Acyclic: No!";
    }

    if (visited.find(node) == visited.end()) {
        visited.insert(node);
        cycleNodes.insert(node);

        if (graph.find(node) != graph.end()) {
            for (const auto& child : graph[node]) {
                dfsToCheckCyclesInGraph(graph, child, visited, cycleNodes);
            }
        }

        cycleNodes.erase(node);
    }
}

int main() {
    Graph inputGraph = readInput();

    std::set<char> visited;
    std::set<char> cycleNodes;

    bool isGraphAcyclic = false;
    for (const auto& [node, _] : inputGraph) {
        try {
            if (visited.count(node) == 0) {
                dfsToCheckCyclesInGraph(inputGraph, node, visited, cycleNodes);
            }
        } catch (const char* message) {
            std::cout << message << std::endl;
            isGraphAcyclic = true;
            break;
        }
    }

    if (!isGraphAcyclic) {
        std::cout << "Acyclic: Yes!" << std::endl;
    }

    return 0;
}

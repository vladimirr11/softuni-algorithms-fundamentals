#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using Graph = std::map<std::string, std::vector<std::string>>;

Graph readInput() {
    Graph inputGraph;

    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        std::istringstream istr(line);

        std::string predecessor;
        istr >> predecessor;

        // remove double quotes
        predecessor.erase(std::remove(predecessor.begin(), predecessor.end(), '\"'), predecessor.end());

        inputGraph[predecessor];

        std::string child;
        while (istr >> child) {
            if (child == "->") {
                continue;
            } else {
                size_t quotePos = child.find('"');
                int numCharToRemove = 1;
                while (quotePos != std::string::npos) {
                    child.erase(quotePos, numCharToRemove);
                    quotePos = child.find('"');
                }

                size_t commaPos = child.find(',');
                if (commaPos != std::string::npos) {
                    child.erase(commaPos, numCharToRemove);
                }

                inputGraph[predecessor].push_back(child);
            }
        }
    }

    return inputGraph;
}

std::map<std::string, int> getPredecessorsCount(Graph& graph) {
    std::map<std::string, int> predecessorsCount;

    for (const auto& [source, childs] : graph) {
        if (!predecessorsCount.count(source)) {
            predecessorsCount[source] = 0;
        }

        for (const auto& child : childs) {
            if (!predecessorsCount.count(child)) {
                predecessorsCount[child] = 0;
            }

            predecessorsCount[child]++;
        }
    }

    return predecessorsCount;
}

void dfsTopSort(std::vector<std::string>& sortedNodes, const std::string& node, 
                Graph& graph, std::set<std::string>& visited, std::set<std::string>& cycleNodes) {
    
    if (cycleNodes.find(node) != cycleNodes.end()) {
        std::cout << "Cycle detected!" << std::endl;
        return; 
    }

    if (visited.find(node) == visited.end()) {
        visited.insert(node);
        cycleNodes.insert(node);
        
        for (const auto& child : graph[node]) {
            dfsTopSort(sortedNodes, child, graph, visited, cycleNodes);
        }

        cycleNodes.erase(node);
        sortedNodes.push_back(node);
    }
}

std::vector<std::string> sortGraphTopologicallyUsingDFS(Graph& graph, std::map<std::string, int>& predsCount) {
    std::vector<std::string> sortedNodes;

    std::set<std::string> visited;
    std::set<std::string> cycleNodes;
    for (const auto& [node, _] : graph) {
        dfsTopSort(sortedNodes, node, graph, visited, cycleNodes);
    }

    // DFS finds the nodes in reverse order so we have to reverse them
    std::reverse(sortedNodes.begin(), sortedNodes.end());

    return sortedNodes;
}

void printSortedGraphNodes(std::vector<std::string>& sortedNodes) {
    for (const auto& node : sortedNodes) {
        std::cout << node << std::endl;
    }
}

int main() {
    // read input graph
    Graph graph = readInput();

    // get each node's predecessors count (each node's dependencies)
    std::map<std::string, int> predecessorsCount = getPredecessorsCount(graph);

    // sort the graph nodes using DFS topological sorting algorithm
    std::vector<std::string> sortedGraphNodes = sortGraphTopologicallyUsingDFS(graph, predecessorsCount);

    printSortedGraphNodes(sortedGraphNodes);

    return 0;
}

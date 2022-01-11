#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
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

std::vector<std::string> sortGraphTopologically(Graph& graph, std::map<std::string, int>& predsCount) {
    std::vector<std::string> sortedNodes;

    while (!predsCount.empty()) {
        std::string nodeWithoutPreds;

        for (const auto& [node, numPreds] : predsCount) {
            if (numPreds == 0) {
                nodeWithoutPreds = node;
                // select child nodes of the current node without predecessors
                auto childNodesOfPred = graph[nodeWithoutPreds];

                // decrement the child nodes preds count as they lose predecessor
                for (auto child : childNodesOfPred) {
                    if (predsCount[child] >= 1) {
                        predsCount[child]--;
                    }
                }

                break;
            }
        }

        if (nodeWithoutPreds == "") {
            break;
        }

        sortedNodes.push_back(nodeWithoutPreds);
        predsCount.erase(nodeWithoutPreds);
    }

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

    // sort the nodes using source (predecessor) removal algorithm
    std::vector<std::string> sortedGraphNodes = sortGraphTopologically(graph, predecessorsCount);

    printSortedGraphNodes(sortedGraphNodes);

    return 0;
}

// "A" -> "B", "C"
// "B" -> "D", "E"
// "C" -> "F"
// "D" -> "C", "F"
// "E" -> "D"
// "F" ->


// "IDEs" -> "variables", "loops"
// "variables" -> "conditionals", "loops", "bits"
// "conditionals" -> "loops"
// "loops" -> "bits"
// "bits"

// "5" -> "11"
// "7" -> "11", "8"
// "8" -> "9"
// "11" -> "9", "10", "2"
// "9" ->
// "3" -> "8", "10"
// "2" ->
// "10"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <map>
#include <deque>
#include <algorithm>

using Graph = std::map<int, std::vector<int>>;

std::tuple<Graph, std::vector<std::pair<int, int>>> readInput() {
    Graph inputGraph;

    int numVertices = 0, numPairs = 0;
    std::cin >> numVertices >> numPairs;

    // inputGraph.resize(numVertices + 1);

    for (int i = 0; i < numVertices; i++) {
        std::string line;
        std::getline(std::cin >> std::ws, line);

        std::istringstream istr(line);

        std::string vertex;
        std::getline(istr >> std::ws, vertex, ':');

        int childs;
        while (istr >> childs) {
            inputGraph[stoi(vertex)].push_back(childs);
        }
    }

    std::vector<std::pair<int, int>> pairs;
    
    for (int i = 0; i < numPairs; i++) {
        std::string pair;
        std::getline(std::cin >> std::ws, pair);

        std::istringstream pairStream(pair);

        std::string src, dest;
        std::getline(pairStream >> std::ws, src, '-');
        std::getline(pairStream >> std::ws, dest, '-');

        pairs.push_back(std::make_pair(stoi(src), stoi(dest)));
    }

    return std::make_tuple(inputGraph, pairs);
}

void printTraversedPath(int src, int dest, std::map<int, int>& traversedPath) {

    std::vector<int> shortestPath;

    shortestPath.push_back(dest);

    int parent = traversedPath[dest];
    while (traversedPath.find(parent) != traversedPath.end()) {
        shortestPath.push_back(parent);
        parent = traversedPath[parent];
    }
    
    if (shortestPath.size() > 1) {
        std::cout << "{" << src << ", " << dest << "} -> " << shortestPath.size() - 1 << std::endl;
    } else {
        std::cout << "{" << src << ", " << dest << "} -> -1" << std::endl;
    }

}

std::map<int, int> bfsShortestPath(Graph& graph, int startNode, int endNode) {
    
    std::deque<int> queue;

    std::map<int, bool> visited;
    std::map<int, int> traversedPath;

    visited[startNode] = true;

    // initialize traversed path with the start node and invalid parent (-1)
    traversedPath[startNode] = -1;

    queue.push_back(startNode);
    while (!queue.empty()) {
        int qFrontNode = queue.front();
        queue.pop_front();

        if (qFrontNode == endNode) {
            return traversedPath;
        }

        for (const int child : graph[qFrontNode]) {
            if (!visited[child]) {
                visited[child] = true;

                traversedPath[child] = qFrontNode;
                queue.push_back(child);
            } 
        }
    }

    return traversedPath;
}

void findShortestDistenceBetweenSrcAndDestNodeUsingBFS(Graph& graph, std::vector<std::pair<int, int>>& pairs) {

    for (int i = 0; i < pairs.size(); i++) {
        // pairs[i].first == current source (start) node, pairs[i].second == current destination node
        auto traversedPath = bfsShortestPath(graph, pairs[i].first, pairs[i].second);

        printTraversedPath(pairs[i].first, pairs[i].second, traversedPath);
    }

}

int main() {
    auto [graph, pairs] = readInput();

    findShortestDistenceBetweenSrcAndDestNodeUsingBFS(graph, pairs);

    return 0;
}

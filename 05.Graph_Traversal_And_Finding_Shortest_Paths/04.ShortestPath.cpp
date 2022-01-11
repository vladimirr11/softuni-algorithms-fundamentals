#include <iostream>
#include <vector>
#include <tuple>
#include <deque>
#include <algorithm>

using Graph = std::vector<std::vector<int>>;

std::tuple<Graph, int, int> readInput() {
    Graph graph;

    int numNodes = 0, numEdges = 0;
    std::cin >> numNodes >> numEdges;

    graph.resize(numNodes + 1);
    for (int edge = 0; edge < numEdges; edge++) {
        int destNode = 0, srcNode = 0;
        std::cin >> destNode >> srcNode;
        graph[destNode].push_back(srcNode);
    }

    int startNode = 0, endNode = 0;
    std::cin >> startNode >> endNode;

    return std::make_tuple(graph, startNode, endNode);
}

void bfsShortestPath(Graph& graph, int startNode, int endNode, 
                     std::vector<bool>& visitedNodes, std::vector<int>& prevNodes) {

    std::deque<int> queue;

    visitedNodes[startNode] = true;

    queue.push_back(startNode);
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop_front();

        if (node == endNode) {
            return;
        }

        for (const int child : graph[node]) {
            if (!visitedNodes[child]) {
                visitedNodes[child] = true;
                // set the current node (child) its parrent (node)!
                prevNodes[child] = node;
                queue.push_back(child);
            }
        }
    }
}   

void print(std::vector<int>& shortestPath) {
    for (const int node : shortestPath) {
        std:: cout << node << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto [graph, startNode, endNode] = readInput();

    std::vector<bool> visitedNodes(graph.size(), false);
    std::vector<int> prevNodes(graph.size(), -1);

    bfsShortestPath(graph, startNode, endNode, visitedNodes, prevNodes);

    // keeps the passed path
    std::vector<int> path;

    path.push_back(endNode);

    // retrive the path from the passed (previous) nodes until reaches invalid index
    int prevNode = prevNodes[endNode];
    while (prevNode != -1) {
        path.push_back(prevNode);
        prevNode = prevNodes[prevNode];
    }

    // reverse the path as we populated it from the end node to the start node
    std::reverse(path.begin(), path.end());

    print(path);

    return 0;
}

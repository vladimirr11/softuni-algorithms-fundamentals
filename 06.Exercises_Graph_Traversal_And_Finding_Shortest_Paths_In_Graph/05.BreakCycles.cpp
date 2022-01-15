#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <deque>
#include <tuple>
#include <algorithm>

using Graph = std::map<char, std::vector<char>>;

struct Edge {
    char src, dest;
};

std::tuple<Graph, std::vector<Edge>> readInput() {
    Graph graph;    
    std::vector<Edge> edges;

    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        std::istringstream istr(line);

        char currNode;
        istr >> currNode;

        if (graph.find(currNode) == graph.end()) {
            graph[currNode];
        }

        char child;
        while (istr >> child) {
            if (child == '-' || child == '>') {
                continue;
            }

            graph[currNode].push_back(child);
            
            Edge currEdge;
            currEdge.src = currNode;
            currEdge.dest = child;
            edges.push_back(currEdge);
        }
    }   

    return std::make_tuple(graph, edges);
}

bool bfsToFindCyclesInGraph(Graph& graph, char startNode, char endNode, 
                            std::map<char, bool>& visitedNodes, std::map<char, char>& prevNodes) {

    std::deque<char> queue;

    visitedNodes[startNode] = true;

    queue.push_back(startNode);
    while (!queue.empty()) {
        char node = queue.front();
        queue.pop_front();

        if (node == endNode) {
            return true;
        }

        for (const auto& child : graph[node]) {
            if (!visitedNodes[child]) {
                visitedNodes[child] = true;
                prevNodes[child] = node;
                queue.push_back(child);
            }
        }
    }

    return false;
}

void print(const std::vector<std::pair<Edge, bool>>& result) {
    for (const auto [edge, isCycleEdge] : result) {
        if (isCycleEdge) {
            std::cout << edge.src << " " << edge.dest << std::endl;
        }
    }
}

int main() {
    auto [graph, edges] = readInput();

    std::sort(edges.begin(), edges.end(), [](const Edge e1, const Edge e2) { 
        if (e1.src < e2.src) {
            return e1.src < e2.src;
        } else if (e1.src == e2.src) {
            return e1.dest < e2.dest;
        } return e1.src < e2.src; } 
    );

    std::map<char, bool> visited;
    std::map<char, char> previousNodes;

    std::vector<std::pair<Edge, bool>> result; 

    for (int currEdge = 0; currEdge < edges.size(); currEdge++) {
        bool isCycleEdge = bfsToFindCyclesInGraph(graph, edges[currEdge].src, edges[currEdge].dest, visited, previousNodes);
        result.emplace_back(std::make_pair(edges[currEdge], isCycleEdge));
        if (!isCycleEdge) {
            visited.clear();
            previousNodes.clear();
        }
    }

    print(result);

    return 0;
}

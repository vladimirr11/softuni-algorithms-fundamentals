#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <tuple>

using Graph = std::map<int, std::vector<int>>;
using Edges = std::vector<std::pair<int, int>>;

std::tuple<Graph, Edges> readInput() {
    Graph graph;
    Edges edges;

    int numVertices = 0, numEdges = 0;
    std::cin >> numVertices >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        std::string line;
        std::getline(std::cin >> std::ws, line);

        std::istringstream istr(line);

        std::string vertex, trash, child;
        istr >> vertex >> trash >> child;

        graph[stoi(vertex)].push_back(stoi(child));
        graph[stoi(child)].push_back(stoi(vertex));

        edges.emplace_back(stoi(vertex), stoi(child));
    }

    return std::make_tuple(graph, edges);
}

void dfsToFindCycles(const Graph& graph, int src, int dest, std::vector<bool>& visited, 
                                   std::set<int>& cycleVertices, std::set<std::set<int>>& unimpVertices) {
    
    if (cycleVertices.find(src) != cycleVertices.end()) {
        unimpVertices.emplace(cycleVertices.begin(), cycleVertices.end());
        return;
    }

    if (!visited[src]) {

        visited[src] = true;
        cycleVertices.insert(src);

        if (graph.find(src) != graph.end()) {
            for (const int child : graph.at(src)) {
                if (child != dest) {
                    dfsToFindCycles(graph, child, src, visited, cycleVertices, unimpVertices);                
                }
            }

            cycleVertices.erase(src);
        }
    }

}

void findEdgesNotPartOfCycle(const Graph& graph, const Edges& edges) {

    for (int i = 0; i < edges.size(); i++) {
        std::set<std::set<int>> cyclesSet;

        std::vector<bool> visited(graph.size(), false);
        std::set<int> cycleVertices;

        dfsToFindCycles(graph, edges[i].first, edges[i].second, visited, cycleVertices, cyclesSet);

        bool isImportantEdge = true;
        for (const auto& vSet : cyclesSet) {
            if (vSet.find(edges[i].first) != vSet.end() && vSet.find(edges[i].second) != vSet.end()) {
                isImportantEdge = false;
            }
        }

        if (isImportantEdge) {
            std::cout << edges[i].first << " " << edges[i].second << std::endl;
        }

    }
}

int main() {
    const auto [graph, edges] = readInput();

    findEdgesNotPartOfCycle(graph, edges);

    return 0;
}

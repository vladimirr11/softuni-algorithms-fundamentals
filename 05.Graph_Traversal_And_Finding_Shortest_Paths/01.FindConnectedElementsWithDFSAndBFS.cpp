#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>

using Graph = std::vector<std::vector<int>>;

Graph readInput() {
    Graph inputGraph;

    int numNodes = 0;
    std::cin >> numNodes;
    std::cin.ignore();

    inputGraph.resize(numNodes);
    for (auto node = 0; node < numNodes; node++) {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream istr(line);
        int currChild = 0;
        while (istr >> currChild) {
            inputGraph[node].push_back(currChild);
        }
    }

    return inputGraph;
}

void dfs(Graph& graph, int startNode, std::vector<int>& adjList, std::vector<bool>& visited) {
    if (!visited[startNode]) {
        visited[startNode] = true;

        // loop over the childs of the current start node 
        // and recursively call dfs to mark all visited childs
        for (const int child : graph[startNode]) {
            dfs(graph, child, adjList, visited);
        }

        // put visited nodes to the adjacency list (connected components of the graph)
        adjList.push_back(startNode);
    }
}

void bfs(Graph& graph, int startNode, std::vector<int>& adjList, std::vector<bool>& visited) {
    std::deque<int> queue;

    // mark the start node as visited
    visited[startNode] = true;

    // put the start node at the back of a queue
    queue.push_back(startNode);

    // loop over the queue until it's empty
    while (!queue.empty()) {
        // take the front node of the queue and add it to the adjacency list
        int node = queue.front();
        queue.pop_front();

        adjList.push_back(node);

        // iterate over the childs of the current front node of the queue and mark all its childs 
        // that are not already visited as so and put those childs to the back of queue
        for (const int child : graph[node]) {
            if (!visited[child]) {
                visited[child] = true;
                queue.push_back(child);
            } 
        }
    }
}

std::vector<std::vector<int>> getConnectedNodes(Graph& graph, std::vector<bool>& visited) {
    std::vector<std::vector<int>> connectedComponents;

    for (int startNode = 0; startNode < graph.size(); startNode++) {
        if (!visited[startNode]) {
            std::vector<int> adjList;
            // dfs(graph, startNode, adjList, visited);
            bfs(graph, startNode, adjList, visited);
            connectedComponents.push_back(adjList);
        }
    }

    return connectedComponents;
}

void printGraphConnectedComponents(const std::vector<std::vector<int>>& connectedComponents) {
    for (const auto& adjList : connectedComponents) {
        std::cout << "Connected components: ";
        for (const int node : adjList) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    Graph graph = readInput();

    // keeps if given node was visited
    std::vector<bool> visited(graph.size(), false);

    // keeps connected components in the graph
    std::vector<std::vector<int>> connectedNodes = getConnectedNodes(graph, visited);
    
    // prints the connceted components in the graph
    printGraphConnectedComponents(connectedNodes);

    return 0;
}

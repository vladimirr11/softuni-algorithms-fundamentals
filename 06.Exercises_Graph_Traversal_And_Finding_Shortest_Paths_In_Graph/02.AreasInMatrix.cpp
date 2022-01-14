#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <deque>
#include <numeric>

using Matrix = std::vector<std::string>;
using AreasMap = std::map<char, int>;

class Edge;
using Graph = std::vector<Edge>;

namespace constants {
    constexpr int arrSize = 2;
    constexpr int invalidIdx = -1;
};

class Edge {
public:
    std::array<int, constants::arrSize> src { constants::invalidIdx, constants::invalidIdx };
    std::array<int, constants::arrSize> dest { constants::invalidIdx, constants::invalidIdx };    

    Edge(int sRow, int sCol) {
        src = { sRow, sCol };
    }

    void setDest(int row, int col) {
        dest = { row, col };
    }

};

Matrix readInput() {
    Matrix matrix;
    
    int numRows = 0;
    std::cin >> numRows;

    matrix.reserve(numRows);
    for (int i = 0; i < numRows; i++) {
        std::string line;
        std::getline(std::cin >> std::ws, line);
        matrix.push_back(line);
    }

    return matrix;
}

bool isInBounds(Matrix& matrix, int row, int col) {
    return row >= 0 && row < matrix.size() && col >= 0 && col < matrix[row].size();
}

void dfsToFindEdgesOfGraphInMatrix(Matrix& matrix, Graph& graph, int row, int col, char currSymbol,
                             std::vector<std::vector<bool>>& visited) {

    visited[row][col] = true;

    Edge edge(row, col);
    graph.push_back(edge);

    if (isInBounds(matrix, row, col + 1) && !visited[row][col + 1] && matrix[row][col + 1] == currSymbol) {
        graph.back().setDest(row, col + 1);
        dfsToFindEdgesOfGraphInMatrix(matrix, graph, row, col + 1, currSymbol, visited);
    }

    if (isInBounds(matrix, row + 1, col) && !visited[row + 1][col] && matrix[row + 1][col] == currSymbol) {
        graph.back().setDest(row + 1, col);
        dfsToFindEdgesOfGraphInMatrix(matrix, graph, row + 1, col, currSymbol, visited);
    }

    if (isInBounds(matrix, row, col - 1) && !visited[row][col - 1] && matrix[row][col - 1] == currSymbol) {
        graph.back().setDest(row, col - 1);
        dfsToFindEdgesOfGraphInMatrix(matrix, graph, row, col - 1, currSymbol, visited);
    }

    if (isInBounds(matrix, row - 1, col) && !visited[row - 1][col] && matrix[row - 1][col] == currSymbol) {
        graph.back().setDest(row - 1, col);
        dfsToFindEdgesOfGraphInMatrix(matrix, graph, row - 1, col, currSymbol, visited);
    }

}

Graph findGraphInMatrix(Matrix& matrix) {
    std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));

    Graph graph;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            char currSymbol = matrix[i][j];
            if (!visited[i][j]) {
                dfsToFindEdgesOfGraphInMatrix(matrix, graph, i, j, currSymbol, visited);
            }
        }
    }

    return graph;
}


void bfsToFindConnectedAreasInGraph(Graph& graph, int startNode, std::vector<bool>& visitedNodes) {
    std::deque<int> queue;

    visitedNodes[startNode] = true;

    queue.push_back(startNode);
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop_front();

        Edge edge = graph[node];
        if (edge.dest[0] != constants::invalidIdx) {
            visitedNodes[node + 1] = true;
            queue.push_back(node + 1);
        }
    }
}

void findConnectedAreasInGraph(Matrix& matrix, Graph& graph, std::vector<bool>& visitedNodes, AreasMap& areasMap) {
    for (int i = 0; i < graph.size(); i++) {
        if (!visitedNodes[i]) {
            Edge edge = graph[i];
            char key = matrix[edge.src[0]][edge.src[1]];
            areasMap[key]++;
            bfsToFindConnectedAreasInGraph(graph, i, visitedNodes);
        }
    }
}

void print(AreasMap& areasMap) {
    int totalAreas = std::accumulate(areasMap.begin(), areasMap.end(), 0, [](int i, std::pair<int, int> pair) {
        return i + pair.second;
    });

    std::cout << "Areas Count: " << totalAreas << std::endl;
    for (const auto& [symbol, numAreas] : areasMap) {
        std::cout << symbol << " -> " << numAreas << " areas" << std::endl;
    }
    
}

int main() {
    Matrix inputMatrix = readInput();

    Graph graph = findGraphInMatrix(inputMatrix);

    std::vector<bool> visitedNodes(graph.size(), false);

    AreasMap areasMap;

    findConnectedAreasInGraph(inputMatrix, graph, visitedNodes, areasMap);

    print(areasMap);

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

using Graph = std::vector<std::vector<int>>;

std::tuple<Graph, std::vector<int>> readInput() {
    Graph graph;

    int numEmplyees = 0;
    std::cin >> numEmplyees;

    graph.resize(numEmplyees);

    std::vector<int> managersCount;
    managersCount.resize(numEmplyees);
    for (int i = 0; i < numEmplyees; i++) {
        std::string line;
        std::getline(std::cin >> std::ws, line);

        for (int j = 0; j < line.size(); j++) {
            if (line[j] == 'Y') {
                managersCount[j]++;
                graph[i].push_back(j);
            }
        }
    }

    int minEl = *std::min_element(managersCount.begin(), managersCount.end());

    std::vector<int> startManagers;
    for (int i = 0; i < managersCount.size(); i++) {
        if (managersCount[i] == minEl) {
            startManagers.push_back(i);
        }
    }

    return std::make_tuple(graph, startManagers);
}

void dfs(const Graph& graph, int node, std::vector<bool>& visited, std::vector<int>& salaries) {
    if (visited[node]) {
        return;
    }

    visited[node] = true;

    for (const auto& child : graph[node]) {
        if (!visited[child]) {
            dfs(graph, child, visited, salaries);

            // work out the sum of salaries for all children (employees) of the current child
            int sum = 0;
            for (int i = 0; i < graph[child].size(); i++) {
                sum += salaries[graph[child][i]];
            }
            // update salaries vec with the current child (employee) salary
            salaries[child] = sum == 0 ? 1 : sum;
        }
    }

    int sum = 0;
    for (int i = 0; i < graph[node].size(); i++) {
        sum += salaries[graph[node][i]];
    }

    salaries[node] = sum == 0 ? 1 : sum;
}

int main() {
    const auto [inputGraph, startManagers] = readInput();

    std::vector<bool> visited(inputGraph.size(), false);
    std::vector<int> salaries(inputGraph.size(), 0);

    for (int i = 0; i < startManagers.size(); i++) {
        dfs(inputGraph, startManagers[i], visited, salaries);
    }

    std::cout << std::accumulate(salaries.begin(), salaries.end(), 0) << std::endl;

    return 0;
}

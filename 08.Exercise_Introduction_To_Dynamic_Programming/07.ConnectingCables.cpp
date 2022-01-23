#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

using DPMemMatrix = std::vector<std::vector<int>>;

std::vector<int> readInput() {
    std::vector<int> cables;

    std::string line;
    std::getline(std::cin >> std::ws, line);
    std::istringstream istr(line);

    int currCableNum {};
    while (istr >> currCableNum) {
        cables.push_back(currCableNum);
    }

    return cables;
}

void construcDpMemMatrixToFindCableConn(std::vector<int>& cables, 
                                        std::vector<int>& destinations, DPMemMatrix& dpMem) {
    
    for (int i = 1; i <= cables.size(); i++) {
        for (int j = 1; j <= cables.size(); j++) {
            if (cables[i - 1] == destinations[j - 1]) {
                dpMem[i][j] = (dpMem[i - 1][j - 1]) + 1;
            } else {
                dpMem[i][j] = std::max(dpMem[i - 1][j], dpMem[i][j - 1]);
            }
        }
    }
}   

void printDpMatrix(DPMemMatrix& dp) {
    for (const auto& row : dp) {
        for (const auto& numInDel : row) {
            std::cout << numInDel << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    auto cables = readInput();

    std::vector<int> destinations(cables.size(), 0);
    std::iota(destinations.begin(), destinations.end(), *std::min_element(cables.begin(), cables.end()));

    DPMemMatrix dpMatrix(cables.size() + 1, std::vector<int>(cables.size() + 1, 0));

    construcDpMemMatrixToFindCableConn(cables, destinations, dpMatrix);

    std::cout << "Maximum pairs connected: " << dpMatrix[cables.size()][cables.size()] << std::endl;

    printDpMatrix(dpMatrix);

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using DPMemMatrix = std::vector<std::vector<int>>;

std::tuple<int, int, int, std::string, std::string> readInput() {
    int replaceCost = 0, insertCost = 0, deleteCost = 0;
    std::cin >> replaceCost >> insertCost >> deleteCost;

    std::string s1, s2;
    std::getline(std::cin >> std::ws, s1);
    std::getline(std::cin >> std::ws, s2);

    return std::make_tuple(replaceCost, insertCost, deleteCost, s1, s2);
}

void constructDpMemMatrixToFindMinEditDistance(DPMemMatrix& dpMem, std::string& s1, const std::string& s2, 
                                               int replaceCost, int insertCost, int deleteCost) {
    
    for (int i = 1; i <= s1.size(); i++) {
        dpMem[i][0] = dpMem[i - 1][0] + deleteCost;
    }

    for (int i = 1; i <= s2.size(); i++) {
        dpMem[0][i] = dpMem[0][i - 1] + insertCost;
    }

    for (int i = 1; i <= s1.size(); i++) {
        for (int j = 1; j <= s2.size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dpMem[i][j] = dpMem[i - 1][j - 1];
            } else {
                int insert = dpMem[i][j - 1] + insertCost;
                int replace = dpMem[i - 1][j - 1] + replaceCost;
                int del = dpMem[i - 1][j] + deleteCost;

                dpMem[i][j] = std::min(insert, std::min(replace, del));
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
    auto [replaceCost, insertCost, deleteCost, s1, s2] = readInput();

    DPMemMatrix dpMatrix(s1.size() + 1, std::vector<int>(s2.size() + 1, 0));

    constructDpMemMatrixToFindMinEditDistance(dpMatrix, s1, s2, replaceCost, insertCost, deleteCost);

    std::cout << "Minimum edit distance: " << dpMatrix[s1.size()][s2.size()] << std::endl;

    printDpMatrix(dpMatrix);

    return 0;
}

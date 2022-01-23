#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

using DPMemMatrix = std::vector<std::vector<int>>;

std::tuple<std::string, std::string> readInput() {
    std::string firstSeq, secondSeq;
    std::getline(std::cin >> std::ws, firstSeq);
    std::getline(std::cin >> std::ws, secondSeq);

    return std::make_tuple(firstSeq, secondSeq);
}

void constructDpMemMatrixToFindMinNumberOfWordDiffs(const std::string& firstSeq, 
                                                    const std::string& secondSeq, DPMemMatrix& dpMatrix) {

    for (int i = 0; i <= firstSeq.size(); i++) {
        for (int j = 0; j <= secondSeq.size(); j++) {
            if (i == 0) {
                dpMatrix[i][j] = j;
            } else if (j == 0) {
                dpMatrix[i][j] = i;
            } else if (firstSeq[i - 1] == secondSeq[j - 1]) {
                dpMatrix[i][j] = dpMatrix[i - 1][j - 1];
            } else {
                dpMatrix[i][j] = std::min(dpMatrix[i - 1][j], dpMatrix[i][j - 1]) + 1;
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
    auto [firstSeq, secondSeq] = readInput();

    // dp memory matrix to store the number of deletions or insertions 
    DPMemMatrix dpMatrix(firstSeq.size() + 1, std::vector<int>(secondSeq.size() + 1, 0));

    constructDpMemMatrixToFindMinNumberOfWordDiffs(firstSeq, secondSeq, dpMatrix);

    std::cout << "Number of InDels: " << dpMatrix[firstSeq.size()][secondSeq.size()] << std::endl;

    printDpMatrix(dpMatrix);

    return 0;
}

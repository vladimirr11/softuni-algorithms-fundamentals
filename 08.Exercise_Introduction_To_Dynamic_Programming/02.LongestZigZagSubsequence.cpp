#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

std::vector<int> readInput() {
    std::vector<int> numbers;

    std::string line;
    std::getline(std::cin >> std::ws, line);
    std::istringstream istr(line);

    int currNum {};
    while (istr >> currNum) {
        numbers.push_back(currNum);
    }

    return numbers;
}

std::tuple<int, std::pair<int, int>> constructDpMemoryAndPrevBestIndicesForZigZagLIS(std::vector<int>& numbers, 
                                std::vector<std::vector<int>>& dpMemory,  std::vector<std::vector<int>>& prevs) {

    // greater numbers row
    dpMemory[0][0] = 1;

    // lesser numbers row
    dpMemory[0][1] = 1;

    int maxLength = 0;
    // bestIndex.first -> maxLength LIS, bestIndex.second -> 0 or 1 row
    std::pair<int, int> bestIndexPos { 0, 0 };

    for (int i = 0; i < numbers.size(); i++) {
        int currentNum = numbers[i];
        for (int j = i - 1; j >= 0; j--) {
            int prevNum = numbers[j];

            if (currentNum > prevNum && dpMemory[i][0] <= dpMemory[j][1] + 1) {
                dpMemory[i][0] = dpMemory[j][1] + 1;
                prevs[i][0] = j;
            } else if (currentNum < prevNum && dpMemory[i][1] <= dpMemory[j][0] + 1) {
                dpMemory[i][1] = dpMemory[j][0] + 1;
                prevs[i][1] = j;
            }
        }

        if (maxLength < dpMemory[i][0]) {
            maxLength = dpMemory[i][0];
            bestIndexPos.first = i;
            bestIndexPos.second = 0;
        } else if (maxLength < dpMemory[i][1]) {
            maxLength = dpMemory[i][1];
            bestIndexPos.first = i;
            bestIndexPos.second = 1;
        }
    }

    return std::make_tuple(maxLength, bestIndexPos);
}

std::vector<int> findLISInPrevBestIndicesVec(std::vector<int>& numbers, std::pair<int, int>& bestIndex, 
                                             std::vector<std::vector<int>>& prevs) {

    std::vector<int> zizagLIS;

    int beginIdx = bestIndex.first;
    int beginRow = bestIndex.second;
    while (beginIdx != -1) {
        zizagLIS.push_back(numbers[beginIdx]);
        beginIdx = prevs[beginIdx][beginRow];
        // zig-zag behaviour (must switch rows each time)
        beginRow = beginRow == 0 ? 1 : 0;
    }

    std::reverse(zizagLIS.begin(), zizagLIS.end());

    return zizagLIS;
}

void printLIS(std::vector<int>& lis) {
    for (const int num : lis) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto numbers = readInput();

    // keeps 2 dp rows -> greater and lesser numbers
    std::vector<std::vector<int>> dpMemory(numbers.size(), std::vector<int>(2, 0));

    // keeps track of the previous best indices for zig-zag LIS 
    std::vector<std::vector<int>> prevs(numbers.size(), std::vector<int>(2, -1));

    auto [maxLength, bestIndexPos] = constructDpMemoryAndPrevBestIndicesForZigZagLIS(numbers, dpMemory, prevs);

    auto zigzagLIS = findLISInPrevBestIndicesVec(numbers, bestIndexPos, prevs);

    printLIS(zigzagLIS);

    return 0;
}

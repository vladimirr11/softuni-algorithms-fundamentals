#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

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

void populateDpMemOfSums(const std::vector<int>& numbers, int totalSum, std::vector<int>& sums) {
    for (int i = 0; i < numbers.size(); i++) {
        int currentValue = numbers[i];
        for (int prevSumIdx = totalSum - currentValue; prevSumIdx >= 0; prevSumIdx--) {
            if (sums[prevSumIdx] != -1 && sums[prevSumIdx + currentValue] == -1) {
                sums[prevSumIdx + currentValue] = i;
            }
        }
    }
}

void printSolution(const std::vector<int>& numbers, int totalSum, std::vector<int>& sums) {
    int half = totalSum / 2;

    for (int i = half; i >= 0; i--) {
        if (sums[i] == -1) {
            continue;
        }

        std::cout << "Differences: " << totalSum - i - i << std::endl;
        std::cout << "Alan: " << i << " Bob: " << totalSum - i << std::endl;
        std::cout << "Alan takes: ";
        while (i != 0) {
            std::cout << numbers[sums[i]] << " ";
            i -= numbers[sums[i]];
        }
        std::cout << "\nBob takes the rest." << std::endl;
    }
}

int main() {
    auto numbers = readInput();

    int totalSum = std::accumulate(numbers.begin(), numbers.end(), 0);

    std::vector<int> sums(totalSum + 1, -1);

    sums[0] = 0;
    populateDpMemOfSums(numbers, totalSum, sums);

    printSolution(numbers, totalSum, sums);

    return 0;
}

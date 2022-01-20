#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

std::tuple<std::vector<int>, int> readInputPrices() {
    std::vector<int> prices;

    std::string line;
    std::getline(std::cin >> std::ws, line);
    std::istringstream istr(line);

    int currPrice = 0;
    while (istr >> currPrice) {
        prices.push_back(currPrice);
    }

    int length = 0;
    std::cin >> length;

    return std::make_tuple(prices, length);
} 

int cutRopeRecursively(int length, std::vector<int>& pricesVec, 
                      std::vector<int>& bestPrices, std::vector<int>& prevBestIndices) {

    if (bestPrices[length] != 0) {
        return bestPrices[length];
    }

    if (length == 0) {
        return 0;
    }

    int currentBest = bestPrices[length];
    for (int i = 1; i <= length; i++) {
        currentBest = 
                std::max(currentBest, pricesVec[i] + cutRopeRecursively(length - i, pricesVec, bestPrices, prevBestIndices));

        if (currentBest > bestPrices[length]) {
            bestPrices[length] = currentBest;
            prevBestIndices[length] = i;
        }
    }

    return bestPrices[length];
}

int cutRopeIteratively(int length, std::vector<int>& pricesVec, 
                      std::vector<int>& bestPrices, std::vector<int>& prevBestIndices) {

    for (int i = 1; i <= length; i++) {
        int currentBest = bestPrices[i];
        for (int j = 1; j <= i; j++) {
            currentBest = std::max(currentBest, pricesVec[j] + bestPrices[i - j]);
            if (currentBest > bestPrices[i]) {
                bestPrices[i] = currentBest;
                prevBestIndices[i] = j;
            }
        }
    }

    return bestPrices[length];
}

void reconstrcutSolution(int length, std::vector<int>& prevBestIndices) {
    while (prevBestIndices[length] != 0) {
        std::cout << prevBestIndices[length] << " ";
        length = length - prevBestIndices[length];
    }
    std::cout << std::endl;
}

int main() {
    auto [pricesVec, length] = readInputPrices();

    std::vector<int> bestPrices(length + 1, 0);
    std::vector<int> prevBestIndices(length + 1, 0);

    // int maxProfit = cutRopeRecursively(length, pricesVec, bestPrices, prevBestIndices);

    int maxProfit = cutRopeIteratively(length, pricesVec, bestPrices, prevBestIndices);

    std::cout << maxProfit << std::endl;

    reconstrcutSolution(length, prevBestIndices);

    return 0;
}

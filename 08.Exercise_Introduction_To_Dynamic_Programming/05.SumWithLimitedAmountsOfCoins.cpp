#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

std::tuple<std::vector<int>, int> readInput() {
    std::vector<int> coins;

    std::string line;
    std::getline(std::cin >> std::ws, line);
    std::istringstream istr(line);

    int currNum {};
    while (istr >> currNum) {
        coins.push_back(currNum);
    }

    int target {};
    std::cin >> target;

    return std::make_tuple(coins, target);
}

template<typename key, typename value>
std::vector<key> getMapKeys(const std::map<key, value>& inputMap) {
    std::vector<key> keysVec;
    keysVec.reserve(inputMap.size());
    for (const auto [k, _] : inputMap) {
        keysVec.push_back(k);
    }

    return keysVec;
}

int findNumOfCoinsCombThatSumUpToTarget(std::vector<int>& coins, int target) {
    std::map<int, int> dpMap { { 0, 0 } };

    int result {};
    for (const int coin : coins) {
        auto keys = getMapKeys(dpMap);
        for (const auto sum : keys) {
            int newSum = coin + sum;

            if (newSum == target) {
                result++;
            }

            if (dpMap.find(newSum) == dpMap.end()) {
                dpMap[newSum] = sum;
            }
        }
    }

    return result;
}

int main() {
    auto [coins, target] = readInput();

    int numComb = findNumOfCoinsCombThatSumUpToTarget(coins, target);

    std::cout << numComb << std::endl;

    return 0;
}

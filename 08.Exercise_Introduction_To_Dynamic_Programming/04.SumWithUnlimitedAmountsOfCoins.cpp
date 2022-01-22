#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
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

void findNumOfCoinsCombThatSumUpToTarget(std::vector<int>& coins, int target, std::vector<int>& dp) {
    dp[0] = 1;
    for (int i = 0; i < coins.size(); i++) {
        int currentCoin = coins[i];
        for (int j = currentCoin; j <= target; j++) {
            dp[j] += dp[j - currentCoin];
        }
    }
}

int main() {
    auto [coins, target] = readInput();

    std::vector<int> dpMem(target + 1, 0);

    findNumOfCoinsCombThatSumUpToTarget(coins, target, dpMem);

    std::cout << "Number of combinations to get " << target << " -> " << dpMem[target] << std::endl;

    return 0;
}

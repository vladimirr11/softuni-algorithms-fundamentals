#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <map>
#include <chrono>

std::tuple<std::vector<int>, int> readInput() {
    std::vector<int> coins;

    std::string line;
    std::getline(std::cin >> std::ws, line);

    std::istringstream istr(line);

    int num = 0;
    while (istr >> num) {
        coins.push_back(num);
    }

    int endSum = 0;
    std::cin >> endSum;

    return std::make_tuple(coins, endSum);
}

std::map<int, int> gatherCoins(std::vector<int>& coins, int sum) {
    std::map<int, int> gatheredCoins;

    // sort from biggest to lowest value
    std::sort(coins.rbegin(), coins.rend());

    // gready approach for finding the best possible coin values
    int index = 0;
    while (sum != 0) {
        // take max possible coins in a turn
        int coinsToTake = sum / coins[index];
        if (coinsToTake != 0) {
            gatheredCoins[coins[index]] += coinsToTake;
        }
        sum %= coins[index];
        index++;
    }

    return gatheredCoins;
}

void print(std::map<int, int>& gatheredCoins) {
    for (auto [coin, number] : gatheredCoins) {
        std::cout << coin << " " << number << std::endl;
    }
}

int main() {
    auto [coins, endSum] = readInput();

    auto start = std::chrono::high_resolution_clock::now();
    std::map<int, int> gatheredCoins = gatherCoins(coins, endSum);
    auto stop = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Execution time: " << time.count() << std::endl;

    if (!gatheredCoins.empty()) {
        print(gatheredCoins); 
    } else {
        std::cout << "No suitable coins!" << std::endl;
    }

    return 0;
}

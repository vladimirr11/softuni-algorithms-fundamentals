#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <tuple>
#include <vector>
#include <algorithm>

std::tuple<std::vector<std::set<int>>, std::set<int>> readInput() {
    std::set<int> universe;

    std::string universLine;
    std::getline(std::cin >> std::ws, universLine);

    std::istringstream istrUnv(universLine);
    std::string univNum;
    while (std::getline(istrUnv >> std::ws, univNum, ',')) {
        universe.insert(stoi(univNum));
    }

    int numSets = 0;
    std::cin >> numSets;

    std::vector<std::set<int>> sets;
    for (int i = 0; i < numSets; i++) {
        std::string line;
        std::getline(std::cin >> std::ws, line);

        std::istringstream istr(line);

        std::set<int> currSet;

        std::string curSetNum;
        while (std::getline(istr >> std::ws, curSetNum, ',')) {
            currSet.insert(stoi(curSetNum));
        }

        sets.push_back(currSet);
    }

    std::sort(sets.begin(), sets.end(), [](std::set<int>& s1, std::set<int>& s2) { 
        return s1.size() > s2.size(); });

    return std::make_tuple(sets, universe);
}

std::vector<std::set<int>> findSubsetOfSetsInUnivers(std::vector<std::set<int>>& sets, std::set<int>& universe) {
    std::vector<std::set<int>> subsets;
    std::set<int> universeCopy;

    // deep copy of universe into universeCopy
    // universeCopy = universe;
    universeCopy.insert(universe.begin(), universe.end());

    auto itSets = sets.begin();
    while (!universeCopy.empty() || itSets != sets.end()) {
        bool shouldPush = false;
        for (auto it = universeCopy.begin(); it != universeCopy.end(); ) {
            if ((*itSets).find(*it) != (*itSets).end()) {
                shouldPush = true;
                universeCopy.erase(it++);
            } else {
                it++;
            }
        }

        if (shouldPush) {
            subsets.push_back(*itSets);
        }

        itSets++;
    }

    return subsets;
}

void print(std::vector<std::set<int>>& subsets) {
    std::cout << "====== Result ======" << std::endl;
    for (const auto& set : subsets) {
        for (const auto& num : set) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    auto [sets, universe] = readInput();

    std::vector<std::set<int>> subsets = findSubsetOfSetsInUnivers(sets, universe);

    print(subsets);

    return 0;
}

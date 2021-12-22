#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <chrono>

using PositionsMap = std::unordered_map<std::string, int>;

PositionsMap getPosData() {
    PositionsMap namePosMap;

    std::string line;
    while (std::getline(std::cin >> std::ws, line)) {
        if (line == "generate") {
            break;
        }

        std::istringstream istr(line);

        std::string name;
        std::string trash;
        int pos = 0;

        istr >> name >> trash >> pos;

        namePosMap[name] = pos;
    }

    return namePosMap;
}

void printSolution(std::vector<std::string>& names) {
    for (auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
}

void distributeFriends(int index, std::vector<std::string>& namesVec, PositionsMap& posMap) {
    if (index == namesVec.size()) {
        for (auto it = posMap.begin(); it != posMap.end(); it++) {
            // decrease pos with -1 to access the right index 
            if (namesVec[(it->second) - 1] != it->first) {
                return;
            }
        }

        printSolution(namesVec);
        return;
    }

    distributeFriends(index + 1, namesVec, posMap);
    for (size_t i = index + 1; i < namesVec.size(); i++) {
        // if (index != (posMap[namesVec[index]] - 1) && i != (posMap[namesVec[i]] - 1)) {
        std::swap(namesVec[index], namesVec[i]);
        distributeFriends(index + 1, namesVec, posMap);
        std::swap(namesVec[index], namesVec[i]);
        // }
    }
}

int main() {
    std::string names;

    std::getline(std::cin >> std::ws, names);

    std::istringstream istr(names);

    std::vector<std::string> namesVec;

    std::string currName;
    while (std::getline(istr >> std::ws, currName, ',')) {
        namesVec.push_back(currName);
    }

    PositionsMap namePosMap = getPosData();

    int startIdx = 0;

    auto startTime = std::chrono::high_resolution_clock::now();
    distributeFriends(startIdx, namesVec, namePosMap);
    auto stopTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    std::cout << duration.count() << std::endl;

    return 0;
}

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using NamesVector = std::vector<std::string>;

using NamesCombVector = std::vector<NamesVector>;

static NamesCombVector girlsCombVec;
static NamesCombVector boysCombVec;

int NUM_GIRLS = 3;
int NUM_BOYS = 2;

NamesVector readInput() {
    NamesVector inputVec;

    std::string line;
    std::getline(std::cin >> std::ws, line);

    std::istringstream istr(line);

    std::string currName;
    while (std::getline(istr >> std::ws, currName, ',')) {
        inputVec.push_back(currName);
    }

    return inputVec;
}

void printSolution(NamesCombVector& girlsComb2DVec, NamesCombVector& boysComb2DVec) {
    for (size_t i = 0; i < girlsComb2DVec.size(); i++) {
        for (size_t j = 0; j < boysComb2DVec.size(); j++) {
            // print each girls' combination for all boys combinations
            for (size_t k = 0; k < NUM_GIRLS; k++) {
                std::cout << girlsComb2DVec[i][k] << ", ";
            }
            // iterate over and print boys combination for each girls' combination
            for (size_t g = 0; g < NUM_BOYS; g++) {
                std::cout << boysComb2DVec[j][g] << ", ";
            }

            // cursor moves 2 '\b' (backspace) backwards and output ' ' instead ', '
            std::cout << "\b\b " << std::endl;
        }
    }
}

void combineGirls(int index, int start, NamesVector& girls, NamesVector& comb) {
    if (index == NUM_GIRLS) {
        girlsCombVec.push_back(comb);
        return;
    }

    for (size_t i = start; i < girls.size(); i++) {
        comb[index] = girls[i];
        combineGirls(index + 1, i + 1, girls, comb);
    }
}

void combineBoys(int index, int start, NamesVector& boys, NamesVector& comb) {
    if (index == NUM_BOYS) {
        boysCombVec.push_back(comb);
        return;
    }

    for (size_t i = start; i < boys.size(); i++) {
        comb[index] = boys[i];
        combineBoys(index + 1, i + 1, boys, comb);
    }
}


int main() {
    NamesVector girls = readInput();
    NamesVector boys = readInput();

    NamesVector gComb(girls.size()), bComb(boys.size());
    
    int index = 0, start = 0;
    combineGirls(index, start, girls, gComb);
    combineBoys(index, start, boys, bComb);

    printSolution(girlsCombVec, boysCombVec);

    return 0;
}

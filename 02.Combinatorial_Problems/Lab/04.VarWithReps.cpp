#include <iostream>
#include <vector>
#include <string>
#include <sstream>

template<typename T>
std::vector<T> readInput() {
    std::vector<T> vec;

    std::string line;
    getline(std::cin, line);

    std::istringstream istr(line);

    T currEl;
    while (istr >> currEl) {
        vec.push_back(currEl);
    }

    return vec;
}

template<typename T>
void printSolution(std::vector<T>& vec) {
    for (auto c : vec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

void varWithRep(int index, 
                std::vector<char>& elementsVec, 
                std::vector<char> varKSlots, 
                std::vector<bool> used) {

    if (index == varKSlots.size()) {
        printSolution(varKSlots);
        return;
    }

    for (int i = 0; i < elementsVec.size(); i++) {
        used[i] = true;
        varKSlots[index] = elementsVec[i];
        varWithRep(index + 1, elementsVec, varKSlots, used);
    }
    
}

int main() {
    std::vector<char> charsVec = readInput<char>(); // example input -> A B C

    int kSlots = 2; // must be less than input vec
    std::vector<char> varKSlots(kSlots);

    std::vector<bool> used(charsVec.size(), false);

    int startIdx = 0;

    varWithRep(startIdx, charsVec, varKSlots, used);

    return 0;
}

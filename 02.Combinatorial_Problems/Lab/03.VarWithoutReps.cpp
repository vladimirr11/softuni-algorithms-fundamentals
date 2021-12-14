#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>

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

void varWithoutRep(int index, 
                   std::vector<char>& elementsVec, 
                   std::vector<char> varKSlots, 
                   std::vector<bool> used) {

    if (index == varKSlots.size()) {
        // bottom
        printSolution(varKSlots);
        return;
    }

    for (int i = 0; i < elementsVec.size(); i++) {
        if (!used[i]) {
            // track
            used[i] = true;
            varKSlots[index] = elementsVec[i];

            // rec call
            varWithoutRep(index + 1, elementsVec, varKSlots, used);

            // back-track
            used[i] = false;
        }
    }
    
}

int main() {
    std::vector<char> charsVec = readInput<char>();

    int kSlots = 2; // must be less than input vec
    std::vector<char> varKSlots(kSlots);

    std::vector<bool> used(charsVec.size(), false); // note the length of the boolean vec must be equal 
                                                    // to the length of the elements vec not to the length of k slots!!

    int startIdx = 0;

    varWithoutRep(startIdx, charsVec, varKSlots, used);

    return 0;
}

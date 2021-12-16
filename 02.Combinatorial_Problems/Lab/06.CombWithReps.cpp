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

void combWithRep(int index, 
                    int start, 
                    std::vector<char>& elementsVec, 
                    std::vector<char> combKSlots) {
    
    if (index == combKSlots.size()) {
        printSolution(combKSlots);
        return;
    }

    for (int i = start; i < elementsVec.size(); i++) {
        combKSlots[index] = elementsVec[i];
        combWithRep(index + 1, i, elementsVec, combKSlots);
    }
}

int main() {
    std::vector<char> charsVec = readInput<char>(); // example input -> A B C

    int kSlots = 2; // must be less than input vec
    std::vector<char> combKSlots(kSlots);

    int index = 0, start = 0;
    combWithRep(index, start, charsVec, combKSlots);

    return 0;
}

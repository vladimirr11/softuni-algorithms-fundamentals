#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<int> readInput() {
    std::vector<int> inputVec;
    
    std::cout << "Enter ws separated array: ";

    std::string arr;
    std::getline(std::cin >> std::ws, arr);
    std::istringstream istr(arr);

    int currNum = 0;
    while (istr >> currNum) {
        inputVec.push_back(currNum);
    }

    return inputVec;
}

void printSolution(std::vector<int>& vec) {
    std::cout << "The reversed array is: ";
    for (auto el : vec) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

void reverseArray(int index, std::vector<int>& elemenst) {
    if (index == elemenst.size() / 2) {
        printSolution(elemenst);
        return;
    }
    
    std::swap(elemenst[index], elemenst[elemenst.size() - 1 - index]);

    reverseArray(index + 1, elemenst);
}

int main() {
    std::vector<int> elementsVec = readInput();

    int startIdx = 0;
    reverseArray(startIdx, elementsVec);

    return 0;
}

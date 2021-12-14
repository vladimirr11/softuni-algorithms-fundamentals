#include <iostream>
#include <vector>
#include <string>
#include <sstream>

static int currEvoke = 1;

std::vector<char> readInput() {
    std::vector<char> charVec;

    std::string line;
    getline(std::cin, line);

    std::istringstream istr(line);

    char currChar;
    while (istr >> currChar) {
        charVec.push_back(currChar);
    }

    return charVec;
}

void printSolution(std::vector<char>& vec) {
    std::cout << currEvoke++ << std::endl;
    for (char c : vec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

void permutateWithoutRep(int startIdx, 
                         std::vector<char>& inputCharVec, 
                         std::vector<char>& permutes, 
                         std::vector<bool>& used) {

    if (startIdx >= inputCharVec.size()) {
        printSolution(permutes);
        return;
    }

    for (int i = 0; i < inputCharVec.size(); i++) {
        if (!used[i]) {
            // tracking
            used[i] = true;
            permutes[startIdx] = inputCharVec[i];

            // recursive call
            permutateWithoutRep(startIdx + 1, inputCharVec, permutes, used);
            
            // backtracking
            used[i] = false;
        }
    }
}

void permuteWithSwap(int index, std::vector<char>& inputCharVec) {

    if (index == inputCharVec.size()) {
        printSolution(inputCharVec);
        return;
    }

    permuteWithSwap(index + 1, inputCharVec);
    for (int i = index + 1; i < inputCharVec.size(); i++) {
        std::swap(inputCharVec[index], inputCharVec[i]);
        permuteWithSwap(index + 1, inputCharVec);
        std::swap(inputCharVec[index], inputCharVec[i]);
    }
    
}

int main() {
    std::vector<char> charVec = readInput();
    std::vector<char> permutes(charVec.size());
    std::vector<bool> used(charVec.size(), false);

    int startIdx = 0;
    // permutateWithoutRep(startIdx, charVec, permutes, used);

    permuteWithSwap(startIdx, charVec); // example input A B C

    return 0;
}

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

void permuteWithRep(int index, std::vector<char>& inputCharVec) {

    if (index == inputCharVec.size()) {
        printSolution(inputCharVec);
        return;
    }

    permuteWithRep(index + 1, inputCharVec);

    std::unordered_set<char> swappedSet;
    swappedSet.insert(inputCharVec[index]);
    for (int i = index + 1; i < inputCharVec.size(); i++) {
        if (swappedSet.find(inputCharVec[i]) == swappedSet.end()) {
            std::swap(inputCharVec[index], inputCharVec[i]);
            permuteWithRep(index + 1, inputCharVec);
            std::swap(inputCharVec[index], inputCharVec[i]);
            swappedSet.insert(inputCharVec[i]);
        }
    }
    
}

// must provide sorted sequence
void permuteWithRepOnSortedIntigers(std::vector<int>& inputVec, int start, int end) {
    printSolution(inputVec);

    for (int left = end - 1; left >= start; left--) {
        for (int right = left + 1; right <= end; right++) {
            if (inputVec[left] != inputVec[right]) {
                std::swap(inputVec[left], inputVec[right]);
                permuteWithRepOnSortedIntigers(inputVec, left + 1, end);
            }
        }

        int firstEl = inputVec[left];
        for (int i = left; i <= end - 1; i++) {
            inputVec[i] = inputVec[i + 1];
        }

        inputVec[end] = firstEl;
    }    
}

int main() {
    // std::vector<char> charVec = readInput<char>(); // example input -> A B B

    std::vector<int> intVec = readInput<int>(); // example input -> 1 3 5 5 5 

    int startIdx = 0;

    permuteWithRepOnSortedIntigers(intVec, 0, intVec.size() - 1);

    return 0;
}

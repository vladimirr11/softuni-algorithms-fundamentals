#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> readInput() {
    std::vector<int> inputVec;
    std::cout << "Enter the count of numbers to sort: ";

    unsigned int n = 0;
    std::cin >> n;

    inputVec.reserve(n);
    for (int i = 0; i < n; i++) {
        int currNum = 0;
        std::cin >> currNum;
        inputVec.push_back(currNum);
    }

    return inputVec;
}

void swap(int& numA, int& numB) {
    int temp = numA;
    numA = numB;
    numB = temp;
}

void selectionSort(std::vector<int>& vecToSort) {
    size_t size = vecToSort.size();
    for (size_t i = 0; i < size - 1; i++) {
        int minIdx = i;

        for (size_t j = i + 1; j < size; j++) {
            if (vecToSort[minIdx] > vecToSort[j]) {
                minIdx = j;
            }
        }

        swap(vecToSort[minIdx], vecToSort[i]);
    }
}

void printSortedVec(std::vector<int>& sortedVec) {
    for (int i : sortedVec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> inputVec = readInput();
    
    selectionSort(inputVec);

    printSortedVec(inputVec);

    return EXIT_SUCCESS;
}

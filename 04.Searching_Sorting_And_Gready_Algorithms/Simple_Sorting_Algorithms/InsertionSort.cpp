#include <iostream>
#include <vector>

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

void insertionSort(std::vector<int>& numsToSort) {
    
    size_t size = numsToSort.size();
    for (size_t i = 1; i < size; i++) {
        int key = numsToSort[i];
        int j = i - 1;

        while (j >= 0 && numsToSort[j] > key) {
            numsToSort[j + 1] = numsToSort[j];
            j--;
        } 

        numsToSort[j + 1] = key;
    }
}

int main() {
    std::vector<int> numbersToSort = readInput();

    insertionSort(numbersToSort);

    for (size_t i = 0; i < numbersToSort.size(); i++) {
        std::cout << numbersToSort[i] << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

#include <iostream>
#include <vector>

std::vector<int> readInput() {
    std::vector<int> inputNumsVec;

    unsigned long countNumsToSort = 0;
    std::cout << "Enter the count of numbers to sort: ";
    std::cin >> countNumsToSort;

    inputNumsVec.reserve(countNumsToSort);
    for (unsigned long i = 0; i < countNumsToSort; i++) {
        int currNum = 0;
        std::cin >> currNum;
        inputNumsVec.push_back(currNum);
    }

    return inputNumsVec;
}

void bubbleSort(std::vector<int>& numsVec) {
    
    size_t size = numsVec.size();
    for (size_t i = 0; i < size - 1; i++) {
        bool isSwapped = false;
        for (size_t j = 0; j < size - i - 1; j++) {
            if (numsVec[j] > numsVec[j + 1]) {
                int temp = numsVec[j];
                numsVec[j] = numsVec[j + 1];
                numsVec[j + 1] = temp;

                isSwapped = true;
            }
        }

        if (!isSwapped) {
            return;
        }
    }

}

int main() {
    std::vector<int> inputNumsVec = readInput();

    bubbleSort(inputNumsVec);

    for (auto num : inputNumsVec) {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}

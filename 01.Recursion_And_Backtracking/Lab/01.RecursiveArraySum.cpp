#include <iostream>

int findRecursiveArraySumRightToLeft(int* array, int currIdx) {
    if (currIdx == 0) {
        return array[currIdx];
    }

    return array[currIdx] + findRecursiveArraySumRightToLeft(array, currIdx - 1 /* --currIdx */);
}

int main() {
    int arrSize;

    std::cout << "Enter array size: ";
    std::cin >> arrSize;

    int* array;
    for (int i = 0; i < arrSize; i++) {
        int currNum = 0;
        std::cout << "Enter number at index " << i << ": ";
        std::cin >> currNum;
        array[i] = currNum;
    }

    int recSumRightLeft = findRecursiveArraySumRightToLeft(array, arrSize - 1);

    std::cout << recSumRightLeft << std::endl;

    return 0;
}

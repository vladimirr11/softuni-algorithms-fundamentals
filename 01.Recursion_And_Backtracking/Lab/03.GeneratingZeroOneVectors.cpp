#include <iostream>

void printArray(int* arr, int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        std::cout << arr[i];
    }
    std::cout << std::endl;

    return;
}

void generateZeroOneVectors(int* arr, int currIdx, int arrSize) {
    // bottom
    if (currIdx < 0) {
        printArray(arr, arrSize);
        return;        
    } 

    // recursive call
    for (int i = 0; i <= 1; i++) {
        arr[currIdx] = i;
        generateZeroOneVectors(arr, currIdx - 1, arrSize);
    }
}

int main() {
    int n = 0;
    std::cout << "Enter number: ";
    std::cin >> n;

    int* arr = new int[n];
    int arrSize = n;

    generateZeroOneVectors(arr, n - 1, arrSize);

    delete[] arr;

    return 0;
}

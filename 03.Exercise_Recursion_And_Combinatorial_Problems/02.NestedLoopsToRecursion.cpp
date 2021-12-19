#include <iostream>
#include <vector>

void printSolution(std::vector<int>& vec) {
    for (auto el : vec) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

void simulateNestedLoopsWithRecursion(std::vector<int>& elements, int index, int n) {
    if (index == n) {
        printSolution(elements);
        return;
    }

    for (int i = 1; i <= n; i++) {
        elements[index] = i;
        simulateNestedLoopsWithRecursion(elements, index + 1, n);
    }
}

int main() {
    int n = 0;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::vector<int> elementsVec(n);

    simulateNestedLoopsWithRecursion(elementsVec, 0, n);

    return 0;
}

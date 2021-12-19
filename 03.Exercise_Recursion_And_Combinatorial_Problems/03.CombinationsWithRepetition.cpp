#include <iostream>
#include <vector>
#include <unordered_set>

void printSolution(std::vector<int>& vec) {
    for (auto el : vec) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

void simulateCombinationsWithoutRep(std::vector<int>& elements, int index, int start, int n, int kSlots) {
    if (index == kSlots) {
        printSolution(elements);
        return;
    }

    for (int i = start; i <= n; i++) {
        elements[index] = i;
        simulateCombinationsWithoutRep(elements, index + 1, i, n, kSlots);
    }
}

int main() {
    int n = 0, k = 0;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::cout << "Enter k: ";
    std::cin >> k;

    std::vector<int> elementsVec(k);

    int index = 0, start = 1;
    simulateCombinationsWithoutRep(elementsVec, index, start, n, k);

    return 0;
}

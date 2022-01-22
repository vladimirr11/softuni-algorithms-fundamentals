#include <iostream>
#include <algorithm>

long findBinomialCoefficient(int n, int k, int** memory) {
    if (k == 0 || k == n) {
        return 1;
    }

    if (memory[n][k] != 0) {
        return memory[n][k];
    }

    return memory[n][k] = findBinomialCoefficient(n - 1, k - 1, memory) + findBinomialCoefficient(n - 1, k, memory);
}

void findBinomCoefIteratevily(int n, int k, int** memory) {
    for (int row = 0; row <= n; row++) {
        for (int col = 0; col <= std::min(row, k); col++) {
            if (col == 0 || col == row) {
                memory[row][col] = 1;
            } else {
                memory[row][col] = memory[row - 1][col] + memory[row - 1][col - 1];
            }
        }
    }
}

int main() {
    int n {}, k {};
    std::cin >> n >> k;

    int** dpMemory = new int*[n + 1];
    for (int i = 0; i < n + 1; i++) {
        dpMemory[i] = new int[k + 1]{};
    }

    // long binCoef = findBinomialCoefficient(n, k, dpMemory);

    findBinomCoefIteratevily(n, k, dpMemory);

    int binCoef = dpMemory[n][k];

    std::cout << binCoef << std::endl;

    for (int i = 0; i <= n; i++) {
        delete[] dpMemory[i];
    }

    return 0;
}

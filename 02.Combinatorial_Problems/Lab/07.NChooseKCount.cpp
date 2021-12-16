#include <iostream>

int calcBinomCoeff(int n, int k) {
    if (k > n) {
        return 0;
    } else if (k == 0 || n == 0) {
        return 1;
    }

    return calcBinomCoeff(n -1, k - 1) + calcBinomCoeff(n - 1, k);
}

int main() {
    int n, k;
    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "Enter k: ";
    std::cin >> k;

    int binCoeff = calcBinomCoeff(n, k);

    std::cout << "N Choose K Count combinations = " << binCoeff << std::endl;

    return 0;
}

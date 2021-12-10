#include <iostream>

unsigned long findNaturalNumberSumRecursively(unsigned int n) {
    if (n == 0) {
        return 1;
    }

    return n * findNaturalNumberSumRecursively(n - 1);
}

int main() {
    unsigned int n = 0;
    std::cout << "Enter n: ";
    std::cin >> n;

    unsigned long r = findNaturalNumberSumRecursively(n);

    std::cout << "n! = " << r << std::endl;

    return EXIT_SUCCESS;
}

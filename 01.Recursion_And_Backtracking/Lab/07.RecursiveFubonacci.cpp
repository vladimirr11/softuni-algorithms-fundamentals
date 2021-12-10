#include <iostream>

int findFibonacci(int n) {
    if (n <= 1) {
        return 1;
    }

    return findFibonacci(n - 1) + findFibonacci(n - 2);
}

int main() {
    std::cout << findFibonacci(5) << std::endl;
    std::cout << findFibonacci(10) << std::endl;
    std::cout << findFibonacci(21) << std::endl;

    return 0;
}

#include <iostream>
#include <vector>

long long recFibWithDP(long long n, long long* memo) {
    if (n <= 2) {
        return memo[n] = 1;
    }

    if (memo[n] != 0) {
        return memo[n];
    }

    return memo[n] = recFibWithDP(n - 1, memo) + recFibWithDP(n - 2, memo);
}

long long* iterFibWithDP(int n, long long* memo) {
    memo[1] = 1, memo[2] = 1;

    for (int i = 3; i <= n; i++) {
        memo[i] = memo[i - 1] + memo[i - 2];
    }

    return memo;
}

long long* iterFibWithDPOptimizedForMemory(int n, long long* memo) {

    long long z = 0, x = 1, y = 1;
    for (int i = 0; i < n; i++) {
        x = y;
        y = z;
        z = x + y;
    }

    memo[0] = z;
    return memo;
}

int main() {
    long long n = 0;
    std::cin >> n;

    long long memo[n + 1]{0};

    // long long fib = recFibWithDP(n, memo);

    // long long* fib = iterFibWithDP(n, memo);

    long long* fib = iterFibWithDPOptimizedForMemory(n, memo);

    std::cout << *fib << std::endl;

    return 0;
}

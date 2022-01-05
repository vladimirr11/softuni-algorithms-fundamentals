#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& numbers, std::vector<int>& counts) {
    for (size_t i = 0; i < numbers.size(); i++) {
        counts[numbers[i]]++;
    }
}

void printSolution(std::vector<int>& counts) {
    for (int i = 0; i <= counts.size(); i++) {
        if (counts[i] != 0) {
            for (int j = 0; j < counts[i]; j++) {
                std::cout << i << " ";
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers { 54, 67, 3, 3, 5, 7, 67, 8 };

    // find the max element 
    auto maxElIt = std::max_element(numbers.begin(), numbers.end());

    // note: the vector size must be the max number + 1
    std::vector<int> counts(*maxElIt + 1);

    countingSort(numbers, counts);

    printSolution(counts);

    return 0;
}

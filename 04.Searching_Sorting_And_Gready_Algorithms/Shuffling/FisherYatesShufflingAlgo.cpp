#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<int> readInput() {
    std::vector<int> numbers;

    std::string line;
    std::getline(std::cin >> std::ws, line);

    std::istringstream istr(line);

    int num = 0;
    while (istr >> num) {
        numbers.push_back(num);
    }

    return numbers;
}

void shuffle(std::vector<int>& numbersVec) {
    size_t size = numbersVec.size();
    for (size_t i = 0; i < size; i++) {
        // exchange array[i] with random element in array[i...n-1]
        size_t r = rand() % size;

        size_t temp = numbersVec[i];
        numbersVec[i] = numbersVec[r];
        numbersVec[r] = temp;
    }
}

void print(std::vector<int>& numbers) {
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = readInput();

    std::sort(numbers.begin(), numbers.end());

    std::cout << "Numbers after sorting:" << std::endl;
    print(numbers);

    shuffle(numbers);

    std::cout << "Numbers after shuffling:" << std::endl;
    print(numbers);

    return 0;
}

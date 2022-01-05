#include <iostream>
#include <vector>
#include <algorithm>

void bucketSort(std::vector<float>& numbers) {
    size_t arrSize = numbers.size();

    // create array::size empty buckets
    std::vector<float> bucket[arrSize];

    // put array elements in differenet buckets
    for (size_t i = 0; i < arrSize; i++) {
        int bIdx = arrSize * numbers[i]; // indx in bucket
        bucket[bIdx].push_back(numbers[i]);
    }

    // sort individual buckets using insertion sort
    for (size_t i = 0; i < arrSize; i++) {
        std::sort(bucket[i].begin(), bucket[i].end());
    }

    // concatenate all buckets into the numbers vector
    int idx = 0;
    for (size_t i = 0; i < arrSize; i++) {
        for (size_t j = 0; j < bucket[i].size(); j++) {
            numbers[idx++] = bucket[i][j];
        }
    }
}

void printSolution(std::vector<float>& numbers) {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<float> numbers { 0.897f, 0.565f, 0.656f, 0.656f, 0.1234f, 0.665f, 0.3434f };

    bucketSort(numbers);

    printSolution(numbers);

    return 0;
}

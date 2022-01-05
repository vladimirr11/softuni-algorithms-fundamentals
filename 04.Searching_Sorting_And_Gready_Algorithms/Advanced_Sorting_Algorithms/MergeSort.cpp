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

void merge(std::vector<int>& array, int start, int mid, int end) {
    if (mid < 0 || mid >= array.size() || array[mid] < array[mid + 1]) {
        return;
    }

    // initialize the left and right sub-array indices 
    // and helper array that will serve for rearranging of data
    int left = start;
    int right = mid + 1;

    std::vector<int> helper(array.size());

    // copy the array data in helper
    for (size_t i = 0; i < array.size(); i++) {
        helper[i] = array[i];
    }

    // rearrange the data
    for (int i = start; i <= end; i++) {
        // security check for index out of bounds exception
        if (left > mid) {
            array[i] = helper[right++];
        // same check as above
        } else if (right > end) {
            array[i] = helper[left++];
        // compare left and right element and take the smaller one
        } else if (helper[left] <= helper[right]) {
            array[i] = helper[left++];
        } else if (helper[left] > helper[right]) {
            array[i] = helper[right++];
        }
    }

}

void mergeSort(std::vector<int>& array, int start, int end) {
    // bottom
    if (start >= end) {
        return;
    }

    int mid = (start + end) / 2;

    // initialize the cleavage of the array into two parts -> left and right
    mergeSort(array, start, mid);
    mergeSort(array, mid + 1, end);

    // backtrack
    merge(array, start, mid, end);

}

void print(std::vector<int>& numbers) {
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> inputNums = readInput();

    int start = 0, end = inputNums.size() - 1;
    mergeSort(inputNums, start, end);
    
    print(inputNums);

    return 0;
}

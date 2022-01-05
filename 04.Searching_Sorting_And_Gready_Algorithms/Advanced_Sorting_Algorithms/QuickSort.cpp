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

int findPartitionPoint(std::vector<int>& array, int start, int end) {
    // this function takes last element as pivot, places the pivot element in its correct position
    // and places all smaller elements to left and all greater elements to right of the pivot

    int pivot = array[end];
    int i = start - 1; // index of smaller element
    for (int j = start; j < end; j++) {
        // if current element is smaller than or equal to pivot
        if (array[j] <= pivot) {
            i++;

            // swap array[i] and array[j]
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // swap array[i + 1] and array[end] or (pivot)
    int temp = array[i + 1];
    array[i + 1] = array[end];
    array[end] = temp;
    
    return i + 1;
}


void quickSort(std::vector<int>& array, int start, int end) {
    if (start < end) {
        // find partition index (pivot) that is now in right place
        int pi = findPartitionPoint(array, start, end);

        // recursively sort elements before partition index and after it
        quickSort(array, start, pi - 1);
        quickSort(array, pi + 1, end);
    }
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
    quickSort(inputNums, start, end);
    
    print(inputNums);

    return 0;
}

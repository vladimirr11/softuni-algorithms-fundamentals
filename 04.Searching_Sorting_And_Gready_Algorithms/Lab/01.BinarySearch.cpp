#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>

using ArrayKeyTuple = std::tuple<std::vector<int>, int>;

ArrayKeyTuple readInput() {
    std::vector<int> vec;

    std::string line;
    std::getline(std::cin >> std::ws, line);

    std::istringstream istr(line);

    int currNum = 0;
    while (istr >> currNum) {
        vec.push_back(currNum);
    }

    int key = 0;
    std::cin >> key;

    return std::make_tuple(vec, key);
}

int binarySearch(std::vector<int>& arr, int key) {
    int start = 0;
    int end = arr.size() - 1;

    while (start <= end) {
        int mid = (start + end) / 2;
        if (arr[mid] < key) {
            start = mid + 1;
        } else if (arr[mid] > key) {
            end = mid - 1;
        } else {
            return mid;
        }
    }

    return EXIT_FAILURE;
}

int main() {
    auto [array, key] = readInput();

    int indexOfKey = binarySearch(array, key);

    std::cout << "Index of " << key << " is " << indexOfKey << std::endl;

    return 0;
}

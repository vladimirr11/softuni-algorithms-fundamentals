#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<int> readInputSequence() {
    std::vector<int> sequence;

    std::string line;
    std::getline(std::cin >> std::ws, line);

    std::istringstream istr(line);

    int currNum;
    while (istr >> currNum) {
        sequence.push_back(currNum);
    }

    return sequence;
}

std::vector<int> findLIS(std::vector<int>& sequence, std::vector<int>& lens, std::vector<int>& prevBestIndices) {
    std::vector<int> lis;
    	
    int maxLength = 0, maxIdx = -1;
    for (int i = 0; i < sequence.size(); i++) {
        int current = sequence[i];

        int bestLength = 1;
        int bestIdx = -1;

        for (int j = i - 1; j >= 0; j--) {
            if (sequence[j] < current && (lens[j] + 1) >= bestLength) {
                bestLength = lens[j] + 1;
                bestIdx = j;
            }
        }

        lens[i] = bestLength;
        prevBestIndices[i] = bestIdx;
        if (maxLength < bestLength) {
            maxLength = bestLength;
            maxIdx = i;
        }
    }

    int index = maxIdx;
    while (index != -1) {
        lis.push_back(sequence[index]);
        index = prevBestIndices[index];
    }

    std::reverse(lis.begin(), lis.end());

    return lis;
}

void print(std::vector<int>& seq) {
    for (const int num : seq) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto sequence = readInputSequence();

    // store for each index of the original sequence
    // the length of the LIS found up to the given index
    std::vector<int> lens(sequence.size(), 0);

    // memorize for each index of the original sequence 
    // the index of the previous largest element
    std::vector<int> prevLargestIdx(sequence.size(), -1);

    auto lis = findLIS(sequence, lens, prevLargestIdx);

    print(lis);

    return 0;
}

// 3 14 5 12 15 7 8 9 11 10 1

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using WordsVector = std::vector<std::string>;
using IndicesTable = std::unordered_map<int, std::vector<std::string>>;

static std::vector<std::string> cruncherVec;
static std::unordered_map<std::string, int> occurancess;

WordsVector readInputWords() {
    WordsVector wordsVec;

    std::string line;
    std::getline(std::cin >> std::ws, line);
    
    std::istringstream istr(line);

    std::string currWord;
    while (std::getline(istr >> std::ws, currWord, ',')) {
        wordsVec.push_back(currWord);
    }

    return wordsVec;
}

void printSolution(WordsVector& words) {
    for (auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

std::string join(std::vector<std::string>& vec) {
    std::string joinedWords;
    for (size_t i = 0; i < vec.size(); i++) {
        joinedWords += vec[i];
    }

    return joinedWords;
}

void permuteWords(int index, IndicesTable& indicesTable, std::string& target) {
    if (index == target.size()) {
        std::string verifyTarget = join(cruncherVec);
        if (verifyTarget == target) {
            printSolution(cruncherVec);
            return;
        }
    	return;
    }
    
    if (indicesTable.find(index) != indicesTable.end()) {
        std::vector<std::string> currIdxStrings = indicesTable[index];
        for (const auto& currStr : currIdxStrings) {
            if (occurancess[currStr] > 0) {
                occurancess[currStr]--;

                cruncherVec.push_back(currStr);
                permuteWords(index + currStr.size(), indicesTable, target);
                cruncherVec.pop_back();
                
                occurancess[currStr]++;
            }
        }
    }
}

int main() {
    WordsVector wordsVec = readInputWords();

    IndicesTable indicesTable;

    std::string target;
    std::getline(std::cin >> std::ws, target);

    // erase all strings that are not in the target
    for (auto it = wordsVec.begin(); it != wordsVec.end(); it++) {
        if (target.find(*it) == std::string::npos) {
            wordsVec.erase(it--);
        }
    }

    // populate a map with keys -> starting indices of any given string in the target
    // and values -> std::vector<std::string> that contains the strings at that starting index
    for (const auto& str : wordsVec) {
        if (occurancess.find(str) != occurancess.end()) {
            occurancess[str] = 0;
        } else {
            occurancess[str]++;
        }

        size_t strIdx = target.find(str);
        
        int startIdx = 1;
        while (strIdx != std::string::npos) {
            if (!indicesTable.count(strIdx)) {
                indicesTable[strIdx];
            }

            indicesTable[strIdx].push_back(str);
            startIdx = strIdx + 1;
            strIdx = target.find(str, startIdx);
        }
    }

    int startIdx = 0;
    permuteWords(startIdx, indicesTable, target);

    return 0;
}

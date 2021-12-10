#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> readLabirinth(int numRows) {
    std::vector<std::string> labirinthVec;
    labirinthVec.reserve(numRows);

    std::string currLine;
    for (int i = 0; i < numRows; i++) {
        getline(std::cin, currLine);
        labirinthVec.push_back(currLine);
    }

    return labirinthVec;
}

bool isInBound(int currRow, int numRows, int currCol, int numCols) {
    return currRow >= 0 && currRow < numRows && currCol >= 0 && currCol < numCols;
}

bool isExit(int currRow, int currCol, std::vector<std::string>& labirinth) {
    if (labirinth[currRow][currCol] == 'e') {
        return true;
    }

    return false;
}

void mark(int currRow, int currCol, std::vector<std::string>& labirinth) {
    labirinth[currRow][currCol] = '+';
}

void unmark(int currRow, int currCol, std::vector<std::string>& labirinth) {
    if (labirinth[currRow][currCol] == '+') {
        labirinth[currRow][currCol] = '-';
    }
}

void findAllPathsInLabirinth(int currRow, int numRows, int currCol, int numCols, 
                             std::string& path, std::vector<std::string>& labirinth, char direction) {

    if (!isInBound(currRow, numRows, currCol, numCols)) {
        return;
    }

    path.push_back(direction);

    if (isExit(currRow, currCol, labirinth)) {
        std::cout << path << std::endl;
        path.pop_back();
        return;
    }

    if (labirinth[currRow][currCol] != '+' && labirinth[currRow][currCol] == '-') {
        mark(currRow, currCol, labirinth);
        findAllPathsInLabirinth(currRow, numRows, currCol + 1, numCols, path, labirinth, direction = 'R');
        findAllPathsInLabirinth(currRow + 1, numRows, currCol, numCols, path, labirinth, direction = 'D');
        findAllPathsInLabirinth(currRow, numRows, currCol - 1, numCols, path, labirinth, direction = 'L');
        findAllPathsInLabirinth(currRow - 1, numRows, currCol, numCols, path, labirinth, direction = 'U');
        unmark(currRow, currCol, labirinth);
    }

    if (!path.empty()) {
        path.pop_back();
    }
}

int main() {
    int numRows, numCols;
    std::cout << "Enter rows' number: ";
    std::cin >> numRows;
    std::cout << "Enter columns' number: ";
    std::cin >> numCols;
    std::cin.ignore();

    std::vector<std::string> labirinthVec = readLabirinth(3);

    std::string path;
    int startRow = 0, startCol = 0;
    char dir;

    findAllPathsInLabirinth(startRow, numRows, startCol, numCols, path, labirinthVec, dir);

    return 0;
}

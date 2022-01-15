#include <iostream>
#include <memory>
#include <deque>

using Matrix = std::unique_ptr<std::unique_ptr<char[]>[]>;
using BoolMatrix = std::unique_ptr<std::unique_ptr<bool[]>[]>;

void readInputMatrix(Matrix& matrix, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        matrix[i] = std::unique_ptr<char[]>(new char[numCols]);
        for (int j = 0; j < numCols; j++) {
            std::cin >> matrix[i][j];
        }
    }
}

bool isInRowBounds(int startRow, int numRows) {
    return startRow >= 0 && startRow < numRows; 
}

bool isInColBounds(int startCol, int numCols) {
    return startCol >= 0 && startCol < numCols; 
}

bool isInBounds(int startRow, int startCol, int numRows, int numCols) {
    return isInRowBounds(startRow, numRows) && isInColBounds(startCol, numCols);
}

void bfsToFillMatrix(Matrix& matrix, int startRow, int startCol, char fillChar, char targetChar,
                     BoolMatrix& visited, int numRows, int numCols) {

    std::deque<std::pair<int, int>> queue;

    visited[startRow][startCol] = true;

    queue.emplace_back(startRow, startCol);
    while (!queue.empty()) {
        std::pair<int, int> pos = queue.front();
        queue.pop_front();

        // check down
        if (isInBounds(pos.first + 1, pos.second, numRows, numCols) && matrix[pos.first + 1][pos.second] == targetChar) {
            visited[pos.first + 1][pos.second] = true;
            matrix[pos.first + 1][pos.second] = fillChar;
            queue.emplace_back(pos.first + 1, pos.second);
        }
        // check up
        if (isInBounds(pos.first - 1, pos.second, numRows, numCols) && matrix[pos.first - 1][pos.second] == targetChar) {
            visited[pos.first - 1][pos.second] = true;
            matrix[pos.first - 1][pos.second] = fillChar;
            queue.emplace_back(pos.first - 1, pos.second);
        }
        // check right
        if (isInBounds(pos.first, pos.second + 1, numRows, numCols) && matrix[pos.first][pos.second + 1] == targetChar) {
            visited[pos.first][pos.second + 1] = true;
            matrix[pos.first][pos.second + 1] = fillChar;
            queue.emplace_back(pos.first, pos.second + 1);
        }
        // check left
        if (isInBounds(pos.first, pos.second - 1, numRows, numCols) && matrix[pos.first][pos.second - 1] == targetChar) {
            visited[pos.first][pos.second - 1] = true;
            matrix[pos.first][pos.second - 1] = fillChar;
            queue.emplace_back(pos.first, pos.second - 1);
        }
    }
}

void printMatrix(Matrix& matrix, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // read matrix dimensions
    int numRows = 0, numCols = 0;
    std::cin >> numRows >> numCols;

    // allocate matrix on the heap
    Matrix matrix(new std::unique_ptr<char[]>[numRows]);

    readInputMatrix(matrix, numRows, numCols);

    // read filling char
    char fillChar;
    std::cin >> fillChar;

    // read start pos in the matrix
    int startRow = 0, startCol = 0;
    std::cin >> startRow >> startCol;

    // allocate 2D bool matrix on the heap to store the visited matrix elements
    BoolMatrix visited(new std::unique_ptr<bool[]>[numRows]);    
    for (int i = 0; i < numRows; i++) {
        visited[i] = std::unique_ptr<bool[]>(new bool[numCols]{false});
    }

    char target = matrix[startRow][startCol];

    bfsToFillMatrix(matrix, startRow, startCol, fillChar, target, visited, numRows, numCols);

    printMatrix(matrix, numRows, numCols);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

using posCountVec = std::vector<std::array<int, 3>>;
using Matrix = std::vector<std::string>;

bool isOutOfBounds(int rows, int cols, int currRow, int currCol) {
    return currRow < 0 || currRow >= rows || currCol < 0 || currCol >= cols;
}

bool isNotTraversal(Matrix matrix, int row, int col) {
    return matrix[row][col] == 'V' || matrix[row][col] == '*';
}

void printSolution(posCountVec& posVec) {
    std::sort(posVec.begin(), posVec.end(), [](std::array<int, 3> first, std::array<int, 3> second){ 
                                                return first[2] > second[2]; });

    std::cout << "Total areas found: " << posVec.size() << std::endl;
    int countArea = 0;
    for (auto& [row, col, count] : posVec) {
        countArea++;
        std::cout << "Area #" << countArea << " at (" << row << ", " << col << "), size: " << count << std::endl;
    }
}

void findAreasInMatrix(Matrix& matrix, int rows, int cols, int currRow, int currCol, posCountVec& posVec) {
    if (isOutOfBounds(rows, cols, currRow, currCol) || isNotTraversal(matrix, currRow, currCol)) {
        return;
    }

    matrix[currRow][currCol] = 'V';

    posVec.back()[2]++;

    findAreasInMatrix(matrix, rows, cols, currRow + 1, currCol, posVec);
    findAreasInMatrix(matrix, rows, cols, currRow, currCol + 1, posVec);
    findAreasInMatrix(matrix, rows, cols, currRow - 1, currCol, posVec);
    findAreasInMatrix(matrix, rows, cols, currRow, currCol - 1, posVec);

}

int main() {
    posCountVec positionsVec;

    int rows = 0, cols = 0;
    
    std::cout << "Enter numRows: ";
    std::cin >> rows;

    std::cout << "Enter numCols: ";
    std::cin >> cols;

    Matrix matrix;
    for (int i = 0; i < rows; i++) {
        std::string line;
        std::getline(std::cin >> std::ws, line);
        matrix.push_back(line);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == '-') {
                std::array<int, 3> arr = { i, j, 0 };
                positionsVec.push_back(arr);
                findAreasInMatrix(matrix, rows, cols, i, j, positionsVec);
            }
        }
    }

    printSolution(positionsVec);

    return 0;
}

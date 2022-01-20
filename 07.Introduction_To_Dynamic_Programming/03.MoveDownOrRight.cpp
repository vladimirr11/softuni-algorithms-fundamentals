#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using Matrix = std::vector<std::vector<int>>;

Matrix readInputMatrix() {
    Matrix matrix;

    int numRows = 0, numCols = 0;
    std::cin >> numRows >> numCols;

    matrix.resize(numRows);
    for (int i = 0; i < numRows; i++) {
        matrix[i].resize(numCols);
        for (int j = 0; j < numCols; j++) {
            std::cin >> matrix[i][j];
        }
    }

    return matrix;
}

void calcHighestSumPathsMatrix(Matrix& inputMatrix, Matrix& outputMatrix) {

    outputMatrix[0][0] = inputMatrix[0][0];

    // works out the values for the first row of the output matrix
    for (int col = 1; col < inputMatrix[0].size(); col++) {
        outputMatrix[0][col] = inputMatrix[0][col] + outputMatrix[0][col - 1];
    }

    // works out the values for the first col of the output matrix
    for (int row = 1; row < inputMatrix.size(); row++) {
        outputMatrix[row][0] = inputMatrix[row][0] + outputMatrix[row - 1][0];
    }

    // works out the values for the rest of the output matrix
    for (int i = 1; i < inputMatrix.size(); i++) {
        for (int j = 1; j < inputMatrix.size(); j++) {
            int currMaxVal = std::max(outputMatrix[i - 1][j], outputMatrix[i][j - 1]);
            outputMatrix[i][j] = inputMatrix[i][j] + currMaxVal;
        }
    }

}

std::vector<std::pair<int, int>> findTheHighestSumPath(Matrix& dpMatrix) {
    std::vector<std::pair<int, int>> path;

    int row = dpMatrix.size() - 1, col = dpMatrix[0].size() - 1;

    path.emplace_back(row, col);

    while (row > 0 || col > 0) {
        int upEl = -1;
        if (row > 0) {
            upEl = dpMatrix[row - 1][col];
        }

        int leftEl = -1;
        if (col > 0) {
            leftEl = dpMatrix[row][col - 1];
        }

        if (upEl > leftEl) {
            row--;
        } else {
            col--;
        }

        path.emplace_back(row, col);
    }

    std::reverse(path.begin(), path.end());

    return path;
}

void printMatrix(Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

void printPath(std::vector<std::pair<int, int>>& path) {
    for (const auto& [row, col] : path) {
        std::cout << "[" << row << ", " << col << "]" << std::endl;
    }
}

int main() {
    Matrix inputMatrix = readInputMatrix();
    
    // assign same dimensions to the output matrix as the input matrix
    Matrix outputMatrix;
    outputMatrix.resize(inputMatrix.size());
    for (int i = 0; i < outputMatrix.size(); i++) {
        outputMatrix[i].resize(inputMatrix[i].size());
    }

    // works out the value of each tile in the matrix based on the previous highest values
    // using combination of gready approach and dynamic programming
    calcHighestSumPathsMatrix(inputMatrix, outputMatrix);

    printMatrix(outputMatrix);

    auto path = findTheHighestSumPath(outputMatrix);

    printPath(path);

    return 0;
}

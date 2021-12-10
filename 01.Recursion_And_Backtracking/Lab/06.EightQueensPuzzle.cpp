#include <iostream>
#include <array>

constexpr int CHESS_BOARD_ROWS = 8;
constexpr int CHESS_BOARD_COLS = 8;

int printCounter = 0;

using Board = std::array<std::array<char, CHESS_BOARD_COLS>, CHESS_BOARD_ROWS>;

void printSolution(Board chessBoard) {
    printCounter++;
    std::cout << printCounter << std::endl;
    for (int i = 0; i < CHESS_BOARD_ROWS; i++) {
        for (int j = 0; j < CHESS_BOARD_COLS; j++) {
            std::cout << chessBoard[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isQueenInUpLeftDiagonal(int row, int col, Board chessBoard) {
    while (row != 0 && col != 0) {
        if (chessBoard[row][col] == 'Q') {
            return true;
        }
        row--;
        col--;
    }

    return false;
}

bool isQueenInUpRightDiagonal(int row, int col, Board chessBoard) {
    while (row != 0 && col != CHESS_BOARD_COLS) {
        if (chessBoard[row][col] == 'Q') {
            return true;
        }
        row--;
        col++;
    }

    return false;
}

bool canPlaceQueen(int row, int col, Board chessBoard) {
    for (int i = 0; i < CHESS_BOARD_ROWS; i++) {
        if (chessBoard[row][i] == 'Q' || chessBoard[i][col] == 'Q') {
            return false;
        }
    }

    if (isQueenInUpLeftDiagonal(row, col, chessBoard) 
        || isQueenInUpRightDiagonal(row, col, chessBoard)) {
        return false;
    }

    return true;
}

void putQueens(Board chessBoard, int row) {
    // bottom
    if (row == CHESS_BOARD_ROWS) {
        printSolution(chessBoard);
        return;
    }

    for (int col = 0; col < CHESS_BOARD_COLS; col++) {
        if (canPlaceQueen(row, col, chessBoard)) {
            // tracking
            chessBoard[row][col] = 'Q';
            // recursive call
            putQueens(chessBoard, row + 1);
            // backtracking
            chessBoard[row][col] = '-';
        }
    }
}

int main() {
    Board chessBoard;
    for (int i = 0; i < chessBoard.size(); i++) {
        for (int j = 0; j < chessBoard[i].size(); j++) {
            chessBoard[i][j] = '-';
        }
    }

    int startRow {};

    putQueens(chessBoard, startRow);

    return 0;
}

#include <iostream>

void printLineOfChars(char charType, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << charType;
    }
    std::cout << std::endl;
}

void drawFigure(int  n) {
    // bottom
    if (n == 0) {
        return;
    }

    // pre-actionss
    printLineOfChars('*', n);
    
    // recursive call
    drawFigure(n - 1);

    // post-actions
    printLineOfChars('#', n);
}

int main() {
    int n = 0;
    std::cout << "Emter number: ";
    std::cin >> n;

    drawFigure(n);

    return 0;
}

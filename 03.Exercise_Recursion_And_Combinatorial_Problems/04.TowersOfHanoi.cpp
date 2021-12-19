#include <iostream>
#include <deque>

static int numSteps = 0;

void printRods(std::deque<int> source, std::deque<int> destination, std::deque<int> spare) {
    std::cout << "Source rod: ";
    while (!source.empty()) {
        std::cout << source.front() << " ";     
        source.pop_front();   
    }
    std::cout << std::endl;

    std::cout << "Destination rod: ";
    while (!destination.empty()) {
        std::cout << destination.front() << " ";     
        destination.pop_front();   
    }
    std::cout << std::endl;

    std::cout << "Spare rod: ";
    while (!source.empty()) {
        std::cout << spare.front() << " ";     
        spare.pop_front();   
    }
    std::cout << "\n" << std::endl;
}

void solveTowersOfHanoi(int numDisks, std::deque<int>& src, std::deque<int>& dest, std::deque<int>& spare) {
    if (numDisks == 1) {
        dest.push_back(src.back());
        src.pop_back();

        std::cout << "Step #" << ++numSteps << std::endl;
        printRods(src, dest, spare);
        return;
    } 
    
    solveTowersOfHanoi(numDisks - 1, src, spare, dest);
    // print current step
    solveTowersOfHanoi(1, src, dest, spare);
    // back-track
    solveTowersOfHanoi(numDisks - 1, spare, dest, src);
    
}

int main() {
    std::deque<int> source;
    std::deque<int> destination;
    std::deque<int> spare;

    int numDisks = 0;
    std::cout << "Enter numDisks: ";
    std::cin >> numDisks;

    for (int i = numDisks; i > 0; i--) {
        source.push_back(i);
    }

    solveTowersOfHanoi(numDisks, source, destination, spare);

    return 0;
}

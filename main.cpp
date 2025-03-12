#include <cstring>
#include <iostream>
#include "polynomial/polynomial.h"

int RunInteractive() { return 0; }

int RunDemo() {
    Term t;
    std::cin >> t;
    std::cout << t << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    bool isInteractive = false;

    if ((argc == 2) && strcmp(argv[1], "i") == 0) {
        isInteractive = true;
    }

    if (isInteractive) {
        return RunInteractive();
    } else {
        return RunDemo();
    }
}

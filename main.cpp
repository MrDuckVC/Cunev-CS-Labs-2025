#include <iostream>
#include "magazineArticle/magazineArticle.h"
#include "planet/planet.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    bool isInteractive = false;

    if ((argc == 2) && strcmp(argv[1], "i") == 0) {
        isInteractive = true;
    }

    if (isInteractive) {
        return magazineArticle::main();
    } else {
        return planet::main();
    }
}

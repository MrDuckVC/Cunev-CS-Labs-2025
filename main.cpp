#include <iostream>
#include "planet/planet.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    bool isInteractive = false;  // по умолчанию демо-режим.

    // Если i передается в качестве аргумента, то программу
    // необходимо запустить в интерактивном режиме
    if ((argc == 2) && strcmp(argv[1], "i") == 0) {
        isInteractive = true;
    }

    if (isInteractive) {
        // return interactive();

    } else {
        return planet::main();
    }
}

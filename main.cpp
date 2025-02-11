#include <iostream>
#include "mymath/mymath.h"
#include "myalphabet/myalphabet.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Я умею суммировать! Зацени 1+1=";
    std::cout << mymath::sum(10, 32) << std::endl;
    std::cout << "Я умею суммировать! Зацени 1+1=";
    std::cout << myalphabet::getLetter(1) << std::endl;

    return 0;
}

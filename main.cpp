#include <cstring>
#include <iostream>
#include "fraction.h"

int RunInteractive() {
    int N_DEC = 4;
    // ввод дроби с клавиатуры
    std::cout << "Введите дробь: \n";
    fraction::Fraction z;
    std::cin >> z;
    std::cout << "z=" << z << std::endl;
    // проверка конструкторов
    fraction::Fraction fr1(10, 14), fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;
    char str[] = "-1 4/8";
    fraction::Fraction fr = str;
    std::cout << "fr=" << fr << std::endl;
    fraction::Fraction x(z), y;
    std::cout << "x=" << x << std::endl;
    double dbl = -1.25;
    fraction::Fraction f = dbl;
    std::cout << "f=" << f << std::endl;
    // проверка перегруженной операции "+"
    y = x + z;
    std::cout << "y=" << y << std::endl;
    y += x;
    f += dbl / 2;
    std::cout << "f=" << f << std::endl;
    y = x + dbl;
    std::cout << "y=" << y << std::endl;
    y = dbl + y;
    std::cout << "y=" << y << std::endl;
    y += dbl;
    std::cout << "y=" << y << std::endl;
    int i = 5;
    y += i;
    std::cout << "y=" << y << std::endl;
    y = i + x;
    std::cout << "y=" << y << std::endl;
    y = x + i;
    std::cout << "y=" << y << std::endl;
    y += dbl + i + x;
    std::cout << "y=" << y << std::endl;
    return 0;
}

int RunDemo() {
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

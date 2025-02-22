#include <cstring>
#include <iostream>
#include "fraction.h"

int RunInteractive() {
    int N_DEC = 4;
    // ввод дроби с клавиатуры
    std::cout << "Введите дробь: \n";
    fraction::Fraction z;
    try {
        std::cin >> z;
    } catch (const std::invalid_argument) {
        std::cout << "Неверная дробь" << std::endl;
        return 1;
    }
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
    std::cout << "Дроби вводятся как строка, имеющая вид:" << std::endl;
    std::cout << "- для дробей с целой частью: знак, целая часть, пробел, числитель, слэш (/), знаменатель. Например: -2 6/18, 5 9/3, 2 4/1." << std::endl;
    std::cout << "- для дробей без целой части: знак, числитель, слэш (/), знаменатель. Например: 3/4, -9/3, -8/6 (знаменатель всегда положительный)." << std::endl;
    std::cout << "- для дробей без дробной части. Например: -2, 0, 4." << std::endl << std::endl;

    char str1[] = "-2 6/18";
    std::cout << "В данном примере дробь равна `" << str1 << "`." << std::endl;
    fraction::Fraction z = str1;
    std::cout << "z = " << z << std::endl;
    // проверка конструкторов
    fraction::Fraction fr1(10, 14), fr2;
    std::cout << "fr2 = " << fr2 << std::endl;
    std::cout << "fr1 = " << fr1 << std::endl;
    char str2[] = "-1 4/8";
    fraction::Fraction fr = str2;
    std::cout << "fr = " << fr << std::endl;
    fraction::Fraction x(z), y;
    std::cout << "x = " << x << std::endl;
    double dbl = -1.25;
    fraction::Fraction f = dbl;
    std::cout << "f = " << f << std::endl;
    // проверка перегруженной операции "+"
    y = x + z;
    std::cout << "y = x + z = " << y << std::endl;
    y += x;
    f += dbl / 2;
    std::cout << "f += dbl / 2 = " << f << std::endl;
    y = x + dbl;
    std::cout << "y = x + dbl = " << y << std::endl;
    y = dbl + y;
    std::cout << "y = dbl + y = " << y << std::endl;
    y += dbl;
    std::cout << "y += dbl = " << y << std::endl;
    int i = 5;
    y += i;
    std::cout << "y += 5 = " << y << std::endl;
    y = i + x;
    std::cout << "y = 5 + x = " << y << std::endl;
    y = x + i;
    std::cout << "y = x + 5 = " << y << std::endl;
    y += dbl + i + x;
    std::cout << "y += dbl + i + x = " << y << std::endl;
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

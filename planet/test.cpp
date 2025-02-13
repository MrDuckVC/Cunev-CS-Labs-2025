// overload.cpp  -  запись  структур в  файл перегруженной
// операцией <<
#include <iostream>
#include <fstream>

using namespace std;
struct element { // Определение некоторой структуры
    int nk, nl;
    float zn;
};

//  Операция-функция,   расширяющая действие операции <<
ofstream &operator<<(ofstream &out, element el) {
    out << ' ' << el.nk << ' ' << el.nl << ' ' << el.zn << '\n';
    return out;
}

int main() {
    const int numbeEl = 5; // Количество структур в массиве
    element arel[numbeEl] = {1, 2, 3.45, 2, 3, 4.56,
                             22, 11, 45.6, 3, 24, 4.33, 3, 6, -5.3};
    // Определяем поток и связываем его с новым файлом abc:
    ofstream filel("abc.txt", ios::app);
    if (!filel) {
        cout << "Неудача при открытии файла abc.\n";
        return 1;
    }
    // Запись в файл abc массива структур:
    for (int i = 0; i < numbeEl; i++)
        filel << arel[i];
    return 0;
}

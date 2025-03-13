#include "myvector.h"
#include <cstring>

// template <>
// MyVector<char*>::MyVector(const MyVector& other) {
//     max_size = other.max_size;
//     size = other.size;
//     pdata = new char*[max_size];
//     for (int i = 0; i < size; i++) {
//         pdata[i] = new char[strlen(other.pdata[i]) + 1];
//         strcpy(pdata[i], other.pdata[i]);
//     }
// }  // Конструктор копирования

// template <>
// MyVector<char*>::~MyVector() {
//     for (int i = 0; i < size; i++) {
//         delete[] pdata[i];
//     }
//     delete[] pdata;
// }  // Деструктор

// template <>
// void MyVector<char*>::add_element(char *const & element) {
//     pdata[size] = new char[strlen(element) + 1];
//     strcpy(pdata[size], element);
//     ++size;
//     resize();
// };  // Вставка элемента в конец вектора

// template <>
// bool MyVector<char*>::delete_element(int index) {
//     if (index >= size || index < 0) {
//         return false;
//     }
//     delete[] pdata[index];
//     for (int i = index; i < size - 1; ++i) {
//         pdata[i] = pdata[i + 1];
//     }
//     --size;
//     resize();
//     return true;
// };  // Удаление элемента из произвольного места

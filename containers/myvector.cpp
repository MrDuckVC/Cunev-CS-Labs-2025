#include "myvector.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

// template<typename T>
// MyVector<T>::MyVector(int initial_size) {
//     if (initial_size <= 0) {
//         throw std::invalid_argument("Invalid initial size");
//     }
//     pdata = new T[max_size];
// }

// template<typename T>
// MyVector<T>::MyVector(const MyVector& other) : max_size(other.max_size), size(other.size) {
//     pdata = new T[max_size];
//     std::copy(other.pdata, other.pdata + size, pdata);
// }

// template<typename T>
// MyVector<T>::~MyVector() {
//     delete[] pdata;
// }

// template<typename T>
// void MyVector<T>::add_element(const T& element) {
//     pdata[size++] = element;
//     resize();
// }

// template<typename T>
// bool MyVector<T>::delete_element(int index) {
//     if (index >= size || index < 0) {
//         return false;
//     }
//     for (int i = index; i < size - 1; ++i) {
//         pdata[i] = pdata[i + 1];
//     }
//     --size;
//     resize();
//     return true;
// }

// template<typename T>
// int MyVector<T>::find(const T& element) const {
//     for (int i = 0; i < size; ++i) {
//         if (pdata[i] == element) {
//             return i;
//         }
//     }
//     return -1;
// }

// template<typename T>
// void MyVector<T>::resize() {
//     if (size >= max_size) {
//         max_size *= 2;
//     } else if (size < max_size / 4) {
//         max_size /= 2;
//     }
//     T* new_data = new T[max_size];
//     std::copy(pdata, pdata + size, new_data);
//     delete[] pdata;
//     pdata = new_data;
// }

// template<typename T>
// T& MyVector<T>::operator[](int index) {
//     return pdata[index];
// }

// template<typename T>
// const T& MyVector<T>::operator[](int index) const {
//     return pdata[index];
// }

// template<typename T>
// MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
//     if (this != &other) {
//         delete[] pdata;
//         max_size = other.max_size;
//         size = other.size;
//         pdata = new T[max_size];
//         std::copy(other.pdata, other.pdata + size, pdata);
//     }
//     return *this;
// }

// template<typename T>
// void MyVector<T>::sort() {
//     for (int i = 0; i < size - 1; ++i) {
//         for (int j = i + 1; j < size; ++j) {
//             if (pdata[i] > pdata[j]) {
//                 std::swap(pdata[i], pdata[j]);
//             }
//         }
//     }
// }

template class MyVector<int>;
template class MyVector<char*>;

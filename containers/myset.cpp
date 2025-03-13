#include "myset.h"

// template<typename T>
// bool MySet<T>::is_element(const T& element) const {
//     return this->find(element) != -1;
// }

// template<typename T>
// void MySet<T>::add_element(const T& element) {
//     if (this->find(element) == -1) {
//         MyVector<T>::add_element(element);
//         this->sort();
//     }
// }

// template<typename T>
// void MySet<T>::delete_element(const T& element) {
//     int index = this->find(element);
//     if (index != -1) {
//         MyVector<T>::delete_element(index);
//     }
// }

// template<typename T>
// MySet<T>& MySet<T>::operator+=(const MySet<T>& other) {
    // *this = *this + other;
    // return *this;
// }

// template<typename T>
// MySet<T>& MySet<T>::operator-=(const MySet<T>& other) {
//     *this = *this - other;
//     return *this;
// }

// template<typename T>
// MySet<T>& MySet<T>::operator*=(const MySet<T>& other) {
//     *this = *this * other;
//     return *this;
// }

// template<typename T>
// MySet<T> MySet<T>::operator+(const MySet<T>& other) {
//     MySet<T> result(*this);
//     for (int i = 0; i < other.get_size(); ++i) {
//         result.add_element(other[i]);
//     }
//     return result;
// }

// template<typename T>
// MySet<T> MySet<T>::operator-(const MySet<T>& other) {
//     MySet<T> result(*this);
//     for (int i = 0; i < other.get_size(); ++i) {
//         if (!other.is_element((*this)[i])) {
//             result.add_element((*this)[i]);
//         }
//     }
//     return result;
// }

// template<typename T>
// MySet<T> MySet<T>::operator*(const MySet<T>& other) {
//     MySet<T> result;
//     for (int i = 0; i < this->get_size(); ++i) {
//         if (other.is_element((*this)[i])) {
//             result.add_element((*this)[i]);
//         }
//     }
//     return result;
// }

// template<typename T>
// bool MySet<T>::operator==(const MySet<T>& other) {
//     if (this->get_size() != other.get_size())
//         return false;
//     for (int i = 0; i < this->get_size(); ++i) {
//         if (!other.is_element((*this)[i])) {
//             return false;
//         }
//     }
//     return true;
// }

// template class MySet<int>;
// template class MySet<char*>;

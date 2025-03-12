#ifndef INHERITANCE_MYSET_H
#define INHERITANCE_MYSET_H

#include <iostream>

#include "myvector.h"

template<typename T>
class MySet : public MyVector<T> {
 public:
    using MyVector<T>::MyVector;

    // Даёт true, если элемент-параметр есть в множестве, иначе даёт false
    bool is_element(const T& element) const { return this->find(element) != -1; }
    // Добавляет элемент в множество, если его там ещё нет
    void add_element(const T& element) {
        if (this->find(element) == -1) {
            MyVector<T>::add_element(element);
            this->sort();
        }
    }
    // Удаляет элемент из множества, если он там есть
    void delete_element(const T& element) {
        int index = this->find(element);
        if (index != -1) {
            MyVector<T>::delete_element(index);
        }
    }

    MySet<T>& operator+=(const MySet<T>& other) {
        *this = *this + other;
        return *this;
    }  // Объединение множеств
    MySet<T>& operator-=(const MySet<T>& other) {
        *this = *this - other;
        return *this;
    }  // Разность множеств
    MySet<T>& operator*=(const MySet<T>& other) {
        *this = *this * other;
        return *this;
    }  // Пересечение множеств

    MySet<T> operator+(const MySet<T>& other) {
        MySet<T> result(*this);
        for (int i = 0; i < other.get_size(); ++i) {
            result.add_element(other[i]);
        }
        return result;
    }  // Объединение
    MySet<T> operator-(const MySet<T>& other) {
        MySet<T> result(*this);
        for (int i = 0; i < other.get_size(); ++i) {
            if (other.is_element((*this)[i])) {
                result.delete_element((*this)[i]);
            }
        }
        return result;
    }  // Разность
    MySet<T> operator*(const MySet<T>& other) {
        MySet<T> result;
        for (int i = 0; i < this->get_size(); ++i) {
            if (other.is_element((*this)[i])) {
                result.add_element((*this)[i]);
            }
        }
        return result;
    };  // Пересечение

    bool operator==(const MySet<T>& other) {
        if (this->get_size() != other.get_size())
            return false;
        for (int i = 0; i < this->get_size(); ++i) {
            if (!other.is_element((*this)[i])) {
                return false;
            }
        }
        return true;
    }  // Сравнение: истина, если элементы двух множеств совпадают
};

#endif  // INHERITANCE_MYSET_H

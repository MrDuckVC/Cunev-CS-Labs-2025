#ifndef INHERITANCE_MYVECTOR_H
#define INHERITANCE_MYVECTOR_H

//#include <algorithm>
#include <iostream>

const int MAX_SIZE = 5;

template<typename T>
class MyVector {
 private:
    int max_size = MAX_SIZE;  // размер вектора
    int size = 0;             // количество элементов в векторе
    T* pdata = nullptr;       // указатель, содержащий адрес динамического массива элементов
    void resize() {
        if (size >= max_size) {
            max_size *= 2;
        } else if (size < max_size / 4) {
            max_size /= 2;
        }
        T* new_data = new T[max_size];
        std::copy(pdata, pdata + size, new_data);
        delete[] pdata;
        pdata = new_data;
    };  // Изменение размера вектора max_size при его переполнении или освобождении места

 public:
    MyVector(int initial_size = MAX_SIZE) {
        if (initial_size <= 0) {
            throw std::invalid_argument("Invalid initial size");
        }
        pdata = new T[max_size];
    };  // Конструктор с одним параметром для создания множества размером 1, который имеет значения по
        // умолчанию и поэтому может использоваться для создания пустого множества
    MyVector(const MyVector& other) {
        max_size = other.max_size;
        size = other.size;
        pdata = new T[max_size];
        std::copy(other.pdata, other.pdata + size, pdata);
    };  // Конструктор копирования
    ~MyVector() { delete[] pdata; };  // Деструктор

    void add_element(const T& element) {
        pdata[size++] = element;
        resize();
    };  // Вставка элемента в конец вектора
    bool delete_element(int index) {
        if (index >= size || index < 0) {
            return false;
        }
        for (int i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }
        --size;
        resize();
        return true;
    };  // Удаление элемента из произвольного места
    int find(const T& element) const {
        for (int i = 0; i < size; ++i) {
            if (pdata[i] == element) {
                return i;
            }
        }
        return -1;
    };  // Возвращает индекс элемента или –1, если элемент не найден

    int get_size() const { return size; }          // Для возврата количества элементов вектора
    int get_max_size() const { return max_size; }  // Для возврата размера вектора

    T& operator[](int index) {
        return pdata[index];
    };  // Для возврата элемента вектора (доступ по индексу)
    const T& operator[](int index) const {
        return pdata[index];
    };
    MyVector<T>& operator=(const MyVector<T>& other) {
        if (this != &other) {
            delete[] pdata;
            max_size = other.max_size;
            size = other.size;
            pdata = new T[max_size];
            std::copy(other.pdata, other.pdata + size, pdata);
        }
        return *this;
    };  // Оператор присваивания

    friend std::ostream& operator<<(std::ostream& out, MyVector<T>& v) {
        out << "{";
        for (int i = 0; i < v.get_size(); i++) {
            out << v[i];
            if (i < v.get_size() - 1) {
                out << ", ";
            }
        }
        out << "}";
        return out;
    }

    void sort() {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (pdata[i] > pdata[j]) {
                    std::swap(pdata[i], pdata[j]);
                }
            }
        }
    };  // Для сортировки
};

#endif  // INHERITANCE_MYVECTOR_H

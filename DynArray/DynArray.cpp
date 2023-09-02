// DynArray.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <initializer_list>
#include <algorithm>
using namespace std;

template <typename T>
class DynArray
{
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    // Конструктор с использованием std::initializer_list
    DynArray(initializer_list<T> initList) : size(initList.size()), capacity(initList.size()) 
    {
        data = new T[capacity];
        copy(initList.begin(), initList.end(), data);
    }

    // Конструктор по умолчанию
    DynArray() : size(0), capacity(0), data(nullptr) {}

    // Деструктор
    ~DynArray() 
    {
        delete[] data;
    }

    // Копирующий конструктор
    DynArray(const DynArray& other) : size(other.size), capacity(other.capacity) 
    {
        data = new T[capacity];
        copy(other.data, other.data + size, data);
    }

    // Перемещающий конструктор
    DynArray(DynArray&& other) noexcept : size(other.size), capacity(other.capacity), data(other.data)
    {
        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;
    }

    // Оператор присваивания
    DynArray& operator=(const DynArray& other) 
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        copy(other.data, other.data + size, data);

        return *this;
    }

    // Оператор перемещения
    DynArray& operator=(DynArray&& other) noexcept 
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = other.data;

        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;

        return *this;
    }

    // Оператор (), который возвращает длину массива
    size_t operator()() const 
    {
        return size;
    }

    // Оператор (), который добавляет элемент в конец массива
    void operator()(const T& element)
    {
        if (size >= capacity) 
        {
            // Увеличиваем размер буфера
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
            T* newData = new T[newCapacity];

            // Копируем данные
            copy(data, data + size, newData);

            // Освобождаем старый буфер
            delete[] data;

            // Устанавливаем новый буфер и емкость
            data = newData;
            capacity = newCapacity;
        }

        // Добавляем элемент в конец
        data[size++] = element;
    }

    // Оператор [] для доступа к элементам массива
    T& operator[](size_t index) 
    {
        if (index >= size) 
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Оператор [] для доступа к элементам массива (константная версия)
    const T& operator[](size_t index) const
    {
        if (index >= size) 
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Перегрузка оператора вывода <<
    friend ostream& operator<<(ostream& os, const DynArray& dynArray)
    {
        os << "[";
        for (size_t i = 0; i < dynArray.size; ++i) 
        {
            os << dynArray.data[i];
            if (i < dynArray.size - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

int main() 
{
    DynArray<int> arr = { 1, 2, 3, 4, 5 };

    // Используем оператор () для добавления элемента
    arr(6);

    // Используем оператор () для получения длины массива
    cout << "Array size: " << arr() << endl;

    // Используем оператор [] для доступа к элементам массива
    cout << "Element at index 2: " << arr[2] << endl;

    // Перегрузка оператора вывода <<
    cout << "Array contents: " << arr << endl;

    return 0;
}

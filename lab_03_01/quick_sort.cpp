#include <iostream>
#include <vector>

using namespace std;

// Основная функция быстрой сортировки
void quickSort(vector<int>& arr, int low, int high) {
    // Базовый случай: если низкий индекс больше или равен высокому
    if (low < high) {
        // Разделяем массив и получаем индекс опорного элемента
        int pi = partition(arr, low, high);

        // Рекурсивно сортируем элементы до и после опорного
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Функция для разделения массива
int partition(vector<int>& arr, int low, int high) {
    // Выбираем последний элемент как опорный
    int pivot = arr[high];

    // Индекс меньшего элемента (указывает на правильную позицию опорного)
    int i = low - 1;

    // Проходим по всем элементам от low до high-1
    for (int j = low; j < high; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] <= pivot) {
            i++; // Увеличиваем индекс меньшего элемента
            swap(arr[i], arr[j]); // Меняем местами
        }
    }

    // Помещаем опорный элемент в правильную позицию
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Вспомогательная функция для обмена элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Демонстрация работы функции
int main() {
    vector<int> numbers = {64, 34, 25, 12, 22, 11, 90, 5, 77, 18};

    cout << "Исходный массив:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Вызываем функцию быстрой сортировки
    quickSort(numbers, 0, numbers.size() - 1);

    cout << "Отсортированный массив:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

/*
Пример ввода:
Исходный массив: 64 34 25 12 22 11 90 5 77 18

Пример вывода:
Отсортированный массив: 5 11 12 18 22 25 34 64 77 90
*/

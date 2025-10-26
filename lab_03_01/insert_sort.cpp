#include <iostream>
#include <vector>

    using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();

    // Проходим по всем элементам массива, начиная со второго
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Текущий элемент, который нужно вставить в отсортированную часть
        int j = i - 1;

        // Сдвигаем элементы отсортированной части, которые больше key, вправо
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Вставляем key в правильную позицию
        arr[j + 1] = key;
    }
}

// Демонстрация работы функции
int main() {
    vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};

    cout << "Исходный массив:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Вызываем функцию сортировки
    insertionSort(numbers);

    cout << "Отсортированный массив:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


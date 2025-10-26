#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binarySearch(const vector<int>& arr, int target) {
    /**
     * Бинарный поиск в отсортированном массиве
     */
    int left = 0;                    // Левая граница поиска
    int right = arr.size() - 1;      // Правая граница поиска

    // Пока границы не пересеклись
    while (left <= right) {
        // Находим средний элемент
        int mid = left + (right - left) / 2;

        // Если нашли целевой элемент
        if (arr[mid] == target) {
            return mid;  // Возвращаем индекс элемента
        }

        // Если целевой элемент меньше среднего, ищем в левой половине
        if (target < arr[mid]) {
            right = mid - 1;
        }
        // Если целевой элемент больше среднего, ищем в правой половине
        else {
            left = mid + 1;
        }
    }

    // Элемент не найден
    return -1;
}

// Демонстрация работы функции
int main() {
    // Отсортированный массив для бинарного поиска
    vector<int> numbers = {5, 11, 12, 18, 22, 25, 34, 64, 77, 90};
    int target = 22;

    cout << "Отсортированный массив для поиска:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Ищем элемент: " << target << endl;

    // Вызываем функцию бинарного поиска
    int result = binarySearch(numbers, target);

    // Выводим результат
    if (result != -1) {
        cout << "Элемент " << target << " найден на позиции " << result << endl;
    } else {
        cout << "Элемент " << target << " не найден в массиве" << endl;
    }

    return 0;
}

/*
Пример ввода:
Отсортированный массив для поиска: 5 11 12 18 22 25 34 64 77 90
Ищем элемент: 22

Пример вывода:
Элемент 22 найден на позиции 4
*/

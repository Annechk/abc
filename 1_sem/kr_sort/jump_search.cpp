#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int jumpSearch(const std::vector<int>& arr, int target) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[std::min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    while (arr[prev] < target) {
        prev++;
        if (prev == std::min(step, n)) {
            return -1;
        }
    }

    if (arr[prev] == target) {
        return prev;
    }

    return -1;
}

void jumpSort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

int main() {
    std::vector<int> array = {64, 34, 25, 12, 22, 11, 90, 5};

    std::cout << "Исходный массив: ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    jumpSort(array);

    std::cout << "Отсортированный массив: ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    int target = 22;
    int index = jumpSearch(array, target);
    if (index != -1) {
        std::cout << "Элемент " << target << " найден на позиции " << index << std::endl;
    } else {
        std::cout << "Элемент " << target << " не найден" << std::endl;
    }

    return 0;
}

//Исходный массив: 64 34 25 12 22 11 90 5
//Отсортированный массив: 5 11 12 22 25 34 64 90
//Элемент 22 найден на позиции 3

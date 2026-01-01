#include <iostream>
#include <vector>
#include <algorithm>

void beadSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = *std::max_element(arr.begin(), arr.end());
    int n = arr.size();

    // Создаем "бусины" - двумерный массив
    std::vector<std::vector<bool>> beads(n, std::vector<bool>(max_val, false));

    // Расставляем бусины согласно значениям массива
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arr[i]; j++) {
            beads[i][j] = true;
        }
    }

    // "Падаем" бусинами под действием гравитации
    for (int j = 0; j < max_val; j++) {
        int sum = 0;
        // Считаем количество бусин в каждом столбце
        for (int i = 0; i < n; i++) {
            if (beads[i][j]) {
                sum++;
                beads[i][j] = false;
            }
        }
        // Размещаем бусины внизу столбца
        for (int i = n - sum; i < n; i++) {
            beads[i][j] = true;
        }
    }

    // Восстанавливаем отсортированный массив из бусин
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < max_val && beads[i][j]) {
            j++;
        }
        arr[i] = j;
    }
}

int main() {
    std::vector<int> array = {3, 1, 4, 1, 5, 9, 2, 6};

    std::cout << "Исходный массив: ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    beadSort(array);

    std::cout << "Отсортированный массив: ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

//Исходный массив: 3 1 4 1 5 9 2 6
//Отсортированный массив: 1 1 2 3 4 5 6 9

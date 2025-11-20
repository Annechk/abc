#include <iostream>
#include <vector>
using namespace std;

vector<int> twoOpt(vector<int> path, const vector<vector<int>>& dist) {
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 1; i < path.size() - 2; i++) {
            for (int j = i + 1; j < path.size() - 1; j++) {
                int current = dist[path[i-1]][path[i]] + dist[path[j]][path[j+1]];
                int new_len = dist[path[i-1]][path[j]] + dist[path[i]][path[j+1]];

                if (new_len < current) {
                    int left = i;
                    int right = j;
                    while (left < right) {
                        swap(path[left], path[right]);
                        left++;
                        right--;
                    }
                    improved = true;
                }
            }
        }
    }
    return path;
}

int main() {
    vector<int> path = {0, 1, 2, 3, 0};

    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    cout << "Начальный маршрут: ";
    for (int city : path) {
        cout << city << " ";
    }
    cout << endl;

    vector<int> result = twoOpt(path, dist);

    cout << "Оптимизированный маршрут: ";
    for (int city : result) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}

/* Ввод данных:
- Начальный маршрут: 0 1 2 3 0
- Матрица расстояний:
[0,  10, 15, 20]
[10, 0,  35, 25]
[15, 35, 0,  30]
[20, 25, 30, 0 ]

Вывод программы:
Начальный маршрут: 0 1 2 3 0
Оптимизированный маршрут: 0 1 3 2 0 */

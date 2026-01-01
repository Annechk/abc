#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main() {
    // Создание вложенного списка (мультисписка)
    // vector<vector<string>> для двумерного массива или vector<list<string>> для списка списков
    vector<vector<string>> groups;

    // Добавление внутренних списков
    groups.push_back({"Hong", "Ryan"});
    groups.push_back({"Andry", "Ross"});
    groups.push_back({"Mike", "Smith"});

    cout << "Исходный мультисписок: ";
    for (const auto& group : groups) {
        cout << "[ ";
        for (const auto& name : group) {
            cout << name << " ";
        }
        cout << "] ";
    }
    cout << endl;

    // Преобразование вложенного списка в плоский список
    vector<string> flatList;
    for (const auto& group : groups) {
        flatList.insert(flatList.end(), group.begin(), group.end());
    }

    cout << "Плоский список: ";
    for (const auto& name : flatList) {
        cout << name << " ";
    }
    cout << endl;

    return 0;
}

using namespace std;

int main() {
    // Создание очереди
    queue<string> taskQueue;

    // Добавление элементов в очередь (в конец)
    taskQueue.push("Task 1");
    taskQueue.push("Task 2");
    taskQueue.push("Task 3");

    cout << "Размер очереди: " << taskQueue.size() << endl;
    cout << "Первый элемент: " << taskQueue.front() << endl;

    // Обработка элементов в порядке FIFO (First-In-First-Out)
    cout << "Обработка очереди:" << endl;
    while (!taskQueue.empty()) {
        string current = taskQueue.front(); // Получение первого элемента
        taskQueue.pop(); // Удаление первого элемента
        cout << "Обрабатывается: " << current << endl;
    }

    return 0;
}


using namespace std;

// Структура для демонстрации приоритетной очереди с пользовательскими объектами
struct Task {
    int id;
    string name;
    int priority;

    Task(int i, string n, int p) : id(i), name(n), priority(p) {}

    // Перегрузка оператора < для сравнения по приоритету
    // Для max-heap (элементы с высшим приоритетом первыми)
    bool operator<(const Task& other) const {
        return priority < other.priority; // Для max-heap
    }

    // Для min-heap (элементы с низшим приоритетом первыми)
    // bool operator<(const Task& other) const {
    //     return priority > other.priority; // Для min-heap
    // }
};

// Функция для вывода информации о задаче
ostream& operator<<(ostream& os, const Task& task) {
    os << "Task[id=" << task.id << ", name='" << task.name
       << "', priority=" << task.priority << "]";
    return os;
}

int main() {
    // Приоритетная очередь с натуральным порядком (max-heap по умолчанию)
    priority_queue<int> intQueue;
    intQueue.push(30);
    intQueue.push(10);
    intQueue.push(20);

    cout << "Целочисленная приоритетная очередь (max-heap):" << endl;
    while (!intQueue.empty()) {
        cout << intQueue.top() << endl; // Выведет: 30, 20, 10
        intQueue.pop();
    }

    // Приоритетная очередь для min-heap (наименьший элемент первый)
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(20);

    cout << "\nЦелочисленная приоритетная очередь (min-heap

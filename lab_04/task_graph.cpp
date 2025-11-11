#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

// Структура для представления ребра графа
struct Edge {
    int destination;
    int weight;
    Edge(int dest, int w) : destination(dest), weight(w) {}
};

// Класс графа
class Graph {
private:
    vector<vector<Edge>> adjacencyList;
    int vertices;

public:
    Graph(int v) : vertices(v) {
        adjacencyList.resize(vertices);
    }

    // Добавление ребра в граф
    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].push_back(Edge(destination, weight));
        // Для неориентированного графа добавляем обратное ребро
        adjacencyList[destination].push_back(Edge(source, weight));
    }

    // Алгоритм Дейкстры для поиска кратчайших путей
    vector<int> dijkstra(int start) {
        vector<int> distances(vertices, numeric_limits<int>::max());
        vector<bool> visited(vertices, false);

        distances[start] = 0;

        // Приоритетная очередь: (расстояние, вершина)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int current = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            if (visited[current]) continue;
            visited[current] = true;

            for (const Edge& edge : adjacencyList[current]) {
                int neighbor = edge.destination;
                int weight = edge.weight;

                if (!visited[neighbor]) {
                    int newDistance = currentDistance + weight;
                    if (newDistance < distances[neighbor]) {
                        distances[neighbor] = newDistance;
                        pq.push({newDistance, neighbor});
                    }
                }
            }
        }

        return distances;
    }

    // Поиск кратчайшего пути между двумя вершинами
    vector<int> findShortestPath(int start, int end) {
        vector<int> distances(vertices, numeric_limits<int>::max());
        vector<int> previous(vertices, -1);
        vector<bool> visited(vertices, false);

        distances[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int current = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            if (visited[current]) continue;
            visited[current] = true;

            if (current == end) break;

            for (const Edge& edge : adjacencyList[current]) {
                int neighbor = edge.destination;
                int weight = edge.weight;

                if (!visited[neighbor]) {
                    int newDistance = currentDistance + weight;
                    if (newDistance < distances[neighbor]) {
                        distances[neighbor] = newDistance;
                        previous[neighbor] = current;
                        pq.push({newDistance, neighbor});
                    }
                }
            }
        }

        // Восстановление пути
        vector<int> path;
        if (distances[end] == numeric_limits<int>::max()) {
            return path; // Путь не найден
        }

        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        return path;
    }

    // Обход в глубину
    void dfs(int start, vector<bool>& visited, vector<int>& result) {
        visited[start] = true;
        result.push_back(start);

        for (const Edge& edge : adjacencyList[start]) {
            if (!visited[edge.destination]) {
                dfs(edge.destination, visited, result);
            }
        }
    }

    vector<int> dfsTraversal(int start) {
        vector<bool> visited(vertices, false);
        vector<int> result;
        dfs(start, visited, result);
        return result;
    }

    // Обход в ширину
    vector<int> bfsTraversal(int start) {
        vector<bool> visited(vertices, false);
        vector<int> result;
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);

            for (const Edge& edge : adjacencyList[current]) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    q.push(edge.destination);
                }
            }
        }

        return result;
    }

    // Вывод информации о графе
    void printGraph() {
        cout << "Структура графа:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << "Вершина " << i << " соединена с: ";
            for (const Edge& edge : adjacencyList[i]) {
                cout << edge.destination << "(вес:" << edge.weight << ") ";
            }
            cout << endl;
        }
    }
};

// Демонстрация работы с графом
int main() {
    // Создание графа
    Graph graph(7);

    // Добавление рёбер
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 4);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 5, 6);
    graph.addEdge(4, 6, 5);
    graph.addEdge(5, 6, 2);

    cout << "=== АНАЛИЗ ГРАФА ===" << endl;
    graph.printGraph();

    // Обходы графа
    cout << "\n=== ОБХОДЫ ГРАФА ===" << endl;
    vector<int> dfsResult = graph.dfsTraversal(0);
    cout << "DFS обход начиная с вершины 0: ";
    for (int vertex : dfsResult) {
        cout << vertex << " ";
    }
    cout << endl;

    vector<int> bfsResult = graph.bfsTraversal(0);
    cout << "BFS обход начиная с вершины 0: ";
    for (int vertex : bfsResult) {
        cout << vertex << " ";
    }
    cout << endl;

    // Алгоритм Дейкстры
    cout << "\n=== АЛГОРИТМ ДЕЙКСТРЫ ===" << endl;
    int startVertex = 0;
    vector<int> distances = graph.dijkstra(startVertex);

    cout << "Кратчайшие расстояния от вершины " << startVertex << ":" << endl;
    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] == numeric_limits<int>::max()) {
            cout << "Вершина " << i << ": недостижима" << endl;
        } else {
            cout << "Вершина " << i << ": " << distances[i] << endl;
        }
    }

    // Поиск конкретного пути
    cout << "\n=== ПОИСК КОНКРЕТНЫХ ПУТЕЙ ===" << endl;
    int from = 0, to = 6;
    vector<int> path = graph.findShortestPath(from, to);

    if (!path.empty()) {
        cout << "Кратчайший путь от " << from << " до " << to << ": ";
        for (int vertex : path) {
            cout << vertex;
            if (vertex != to) cout << " -> ";
        }
        cout << endl;

        // Вычисление длины пути
        vector<int> dist = graph.dijkstra(from);
        cout << "Длина пути: " << dist[to] << endl;
    } else {
        cout << "Путь от " << from << " до " << to << " не найден" << endl;
    }

    return 0;
}

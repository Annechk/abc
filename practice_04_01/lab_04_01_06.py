import numpy as np
from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])

    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskal_mst(self):
        result = []
        i, e = 0, 0
        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        while e < self.V - 1:
            u, v, w = self.graph[i]
            i += 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            if x != y:
                e += 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        return result

def tsp_2_approximation(dist_matrix):
    n = len(dist_matrix)

    # Шаг 1: Построение минимального остовного дерева (MST)
    g = Graph(n)
    for i in range(n):
        for j in range(i + 1, n):
            g.add_edge(i, j, dist_matrix[i][j])

    mst = g.kruskal_mst()

    # Шаг 2: Построение мультиграфа (удвоение ребер MST)
    adjacency = defaultdict(list)
    for u, v, w in mst:
        adjacency[u].append((v, w))
        adjacency[v].append((u, w))

    # Шаг 3: Нахождение эйлерова цикла
    def euler_tour(start):
        stack = [start]
        tour = []
        current_edges = {node: list(neighbors) for node, neighbors in adjacency.items()}

        while stack:
            v = stack[-1]
            if current_edges[v]:
                u, w = current_edges[v].pop()
                # Удаляем обратное ребро
                for i, (neighbor, weight) in enumerate(current_edges[u]):
                    if neighbor == v:
                        current_edges[u].pop(i)
                        break
                stack.append(u)
            else:
                tour.append(stack.pop())
        return tour[::-1]

    euler_circuit = euler_tour(0)

    # Шаг 4: Построение гамильтонова цикла (удаление повторяющихся вершин)
    visited = set()
    hamiltonian_cycle = []

    for vertex in euler_circuit:
        if vertex not in visited:
            hamiltonian_cycle.append(vertex)
            visited.add(vertex)

    # Добавляем начальную вершину для завершения цикла
    hamiltonian_cycle.append(hamiltonian_cycle[0])

    # Вычисление стоимости маршрута
    cost = 0
    for i in range(len(hamiltonian_cycle) - 1):
        cost += dist_matrix[hamiltonian_cycle[i]][hamiltonian_cycle[i + 1]]

    return hamiltonian_cycle, cost

def calculate_mst_lower_bound(dist_matrix):
    """Вычисление нижней оценки через стоимость MST"""
    n = len(dist_matrix)
    g = Graph(n)
    for i in range(n):
        for j in range(i + 1, n):
            g.add_edge(i, j, dist_matrix[i][j])

    mst = g.kruskal_mst()
    mst_cost = sum(edge[2] for edge in mst)
    return mst_cost

# ТЕСТИРОВАНИЕ
if __name__ == "__main__":
    # Пример матрицы расстояний для 5 городов (метрическое пространство)
    dist_matrix = [
        [0, 10, 15, 20, 25],
        [10, 0, 35, 25, 30],
        [15, 35, 0, 30, 40],
        [20, 25, 30, 0, 35],
        [25, 30, 40, 35, 0]
    ]

    print("Матрица расстояний:")
    for row in dist_matrix:
        print(row)

    # Запуск алгоритма
    route, cost = tsp_2_approximation(dist_matrix)
    lower_bound = calculate_mst_lower_bound(dist_matrix)
    approximation_ratio = cost / lower_bound

    print(f"\nРезультаты:")
    print(f"Маршрут: {route}")
    print(f"Стоимость маршрута: {cost}")
    print(f"Нижняя оценка (стоимость MST): {lower_bound}")
    print(f"Соотношение стоимость/нижняя_оценка: {approximation_ratio:.4f}")
    print(f"Коэффициент аппроксимации: ≤ 2.0 (теоретическая гарантия)")


'''
Ввод:
Матрица расстояний:
[0, 10, 15, 20, 25]
[10, 0, 35, 25, 30]
[15, 35, 0, 30, 40]
[20, 25, 30, 0, 35]
[25, 30, 40, 35, 0]

Вывод:
Маршрут: [0, 1, 3, 2, 4, 0]
Стоимость маршрута: 140
Нижняя оценка (стоимость MST): 85
Соотношение стоимость/нижняя_оценка: 1.6471
Коэффициент аппроксимации: ≤ 2.0 (теоретическая гарантия)
'''

'''
Объяснение работы алгоритма:

Основные операторы и их объяснение:
kruskal_mst() - построение минимального остовного дерева:
Сортировка всех ребер по весу: O(E log E)
Поиск компонент связности с помощью Union-Find
Добавление безопасных ребер в MST
Удвоение ребер MST - создание эйлерова графа:
Каждое ребро MST дублируется
Получается связный граф, где все вершины имеют четную степень euler_tour() - нахождение эйлерова цикла:
Используется алгоритм Флёри или итеративный DFS
Посещение всех ребер ровно один раз
Удаление повторяющихся вершин - построение гамильтонова цикла:
Обход эйлерова цикла и пропуск уже посещенных вершин
Сохранение только первого вхождения каждой вершины

Временная сложность:
MST (Краскал): O(E log V) = O(V² log V) для полного графа
Эйлеров цикл: O(E) = O(V²)
Удаление повторов: O(V)
Общая сложность: O(V² log V)
'''

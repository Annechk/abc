import heapq
from collections import deque

# Класс графа
class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.adjacency_list = [[] for _ in range(vertices)]

    # Добавление ребра в граф
    def add_edge(self, source, destination, weight):
        self.adjacency_list[source].append((destination, weight))
        # Для неориентированного графа добавляем обратное ребро
        self.adjacency_list[destination].append((source, weight))

    # Алгоритм Дейкстры для поиска кратчайших путей
    def dijkstra(self, start):
        distances = [float('inf')] * self.vertices
        visited = [False] * self.vertices

        distances[start] = 0

        # Приоритетная очередь: (расстояние, вершина)
        heap = [(0, start)]

        while heap:
            current_distance, current_vertex = heapq.heappop(heap)

            if visited[current_vertex]:
                continue
            visited[current_vertex] = True

            for neighbor, weight in self.adjacency_list[current_vertex]:
                if not visited[neighbor]:
                    new_distance = current_distance + weight
                    if new_distance < distances[neighbor]:
                        distances[neighbor] = new_distance
                        heapq.heappush(heap, (new_distance, neighbor))

        return distances

    # Поиск кратчайшего пути между двумя вершинами
    def find_shortest_path(self, start, end):
        distances = [float('inf')] * self.vertices
        previous = [-1] * self.vertices
        visited = [False] * self.vertices

        distances[start] = 0

        heap = [(0, start)]

        while heap:
            current_distance, current_vertex = heapq.heappop(heap)

            if visited[current_vertex]:
                continue
            visited[current_vertex] = True

            if current_vertex == end:
                break

            for neighbor, weight in self.adjacency_list[current_vertex]:
                if not visited[neighbor]:
                    new_distance = current_distance + weight
                    if new_distance < distances[neighbor]:
                        distances[neighbor] = new_distance
                        previous[neighbor] = current_vertex
                        heapq.heappush(heap, (new_distance, neighbor))

        # Восстановление пути
        path = []
        if distances[end] == float('inf'):
            return path  # Путь не найден

        current = end
        while current != -1:
            path.append(current)
            current = previous[current]

        path.reverse()
        return path

    # Обход в глубину
    def _dfs(self, start, visited, result):
        visited[start] = True
        result.append(start)

        for neighbor, _ in self.adjacency_list[start]:
            if not visited[neighbor]:
                self._dfs(neighbor, visited, result)

    def dfs_traversal(self, start):
        visited = [False] * self.vertices
        result = []
        self._dfs(start, visited, result)
        return result

    # Обход в ширину
    def bfs_traversal(self, start):
        visited = [False] * self.vertices
        result = []
        queue = deque([start])
        visited[start] = True

        while queue:
            current = queue.popleft()
            result.append(current)

            for neighbor, _ in self.adjacency_list[current]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append(neighbor)

        return result

    # Вывод информации о графе
    def print_graph(self):
        print("Структура графа:")
        for i in range(self.vertices):
            connections = [f"{dest}(вес:{weight})" for dest, weight in self.adjacency_list[i]]
            print(f"Вершина {i} соединена с: {' '.join(connections)}")

# Демонстрация работы с графом
if __name__ == "__main__":
    # Создание графа
    graph = Graph(7)

    # Добавление рёбер
    edges = [
        (0, 1, 4), (0, 2, 3), (1, 2, 1), (1, 3, 2),
        (2, 3, 4), (2, 4, 3), (3, 4, 2), (3, 5, 1),
        (4, 5, 6), (4, 6, 5), (5, 6, 2)
    ]

    for source, dest, weight in edges:
        graph.add_edge(source, dest, weight)

    print("=== АНА

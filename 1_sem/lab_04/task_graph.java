import java.util.*;

// Класс для представления ребра графа
class Edge {
    int destination;
    int weight;

    public Edge(int dest, int w) {
        this.destination = dest;
        this.weight = w;
    }
}

// Класс для пары (расстояние, вершина) для приоритетной очереди
class Pair implements Comparable<Pair> {
    int distance;
    int vertex;

    public Pair(int distance, int vertex) {
        this.distance = distance;
        this.vertex = vertex;
    }

    @Override
    public int compareTo(Pair other) {
        return Integer.compare(this.distance, other.distance);
    }
}

// Класс графа
class Graph {
    private List<List<Edge>> adjacencyList;
    private int vertices;

    public Graph(int v) {
        this.vertices = v;
        this.adjacencyList = new ArrayList<>();
        for (int i = 0; i < v; i++) {
            adjacencyList.add(new ArrayList<>());
        }
    }

    // Добавление ребра в граф
    public void addEdge(int source, int destination, int weight) {
        adjacencyList.get(source).add(new Edge(destination, weight));
        // Для неориентированного графа добавляем обратное ребро
        adjacencyList.get(destination).add(new Edge(source, weight));
    }

    // Алгоритм Дейкстры для поиска кратчайших путей
    public int[] dijkstra(int start) {
        int[] distances = new int[vertices];
        boolean[] visited = new boolean[vertices];

        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;

        PriorityQueue<Pair> pq = new PriorityQueue<>();
        pq.offer(new Pair(0, start));

        while (!pq.isEmpty()) {
            Pair current = pq.poll();
            int currentVertex = current.vertex;
            int currentDistance = current.distance;

            if (visited[currentVertex]) continue;
            visited[currentVertex] = true;

            for (Edge edge : adjacencyList.get(currentVertex)) {
                int neighbor = edge.destination;
                int weight = edge.weight;

                if (!visited[neighbor]) {
                    int newDistance = currentDistance + weight;
                    if (newDistance < distances[neighbor]) {
                        distances[neighbor] = newDistance;
                        pq.offer(new Pair(newDistance, neighbor));
                    }
                }
            }
        }

        return distances;
    }

    // Поиск кратчайшего пути между двумя вершинами
    public List<Integer> findShortestPath(int start, int end) {
        int[] distances = new int[vertices];
        int[] previous = new int[vertices];
        boolean[] visited = new boolean[vertices];

        Arrays.fill(distances, Integer.MAX_VALUE);
        Arrays.fill(previous, -1);
        distances[start] = 0;

        PriorityQueue<Pair> pq = new PriorityQueue<>();
        pq.offer(new Pair(0, start));

        while (!pq.isEmpty()) {
            Pair current = pq.poll();
            int currentVertex = current.vertex;
            int currentDistance = current.distance;

            if (visited[currentVertex]) continue;
            visited[currentVertex] = true;

            if (currentVertex == end) break;

            for (Edge edge : adjacencyList.get(currentVertex)) {
                int neighbor = edge.destination;
                int weight = edge.weight;

                if (!visited[neighbor]) {
                    int newDistance = currentDistance + weight;
                    if (newDistance < distances[neighbor]) {
                        distances[neighbor] = newDistance;
                        previous[neighbor] = currentVertex;
                        pq.offer(new Pair(newDistance, neighbor));
                    }
                }
            }
        }

        // Восстановление пути
        List<Integer> path = new ArrayList<>();
        if (distances[end] == Integer.MAX_VALUE) {
            return path; // Путь не найден
        }

        for (int at = end; at != -1; at = previous[at]) {
            path.add(at);
        }
        Collections.reverse(path);

        return path;
    }

    // Обход в глубину
    private void dfs(int start, boolean[] visited, List<Integer> result) {
        visited[start] = true;
        result.add(start);

        for (Edge edge : adjacencyList.get(start)) {
            if (!visited[edge.destination]) {
                dfs(edge.destination, visited, result);
            }
        }
    }

    public List<Integer> dfsTraversal(int start) {
        boolean[] visited = new boolean[vertices];
        List<Integer> result = new ArrayList<>();
        dfs(start, visited, result);
        return result;
    }

    // Обход в ширину
    public List<Integer> bfsTraversal(int start) {
        boolean[] visited = new boolean[vertices];
        List<Integer> result = new ArrayList<>();
        Queue<Integer> queue = new LinkedList<>();

        visited[start] = true;
        queue.offer(start);

        while (!queue.isEmpty()) {
            int current = queue.poll();
            result.add(current);

            for (Edge edge : adjacencyList.get(current)) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    queue.offer(edge.destination);
                }
            }
        }

        return result;
    }

    // Вывод информации о графе
    public void printGraph() {
        System.out.println("Структура графа:");
        for (int i = 0; i < vertices; i++) {
            System.out.print("Вершина " + i + " соединена с: ");
            for (Edge edge : adjacencyList.get(i)) {
                System.out.print(edge.destination + "(вес:" + edge.weight + ") ");
            }
            System.out.println();
        }
    }
}

// Демонстрация работы с графом
public class Labграфы {
    public static void main(String[] args) {
        // Создание графа
        Graph graph = new Graph(7);

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

        System.out.println("=== АНАЛИЗ ГРАФА ===");
        graph.printGraph();

        // Обходы графа
        System.out.println("\n=== ОБХОДЫ ГРАФА ===");
        List<Integer> dfsResult = graph.dfsTraversal(0);
        System.out.print("DFS обход начиная с вершины 0: ");
        for (int vertex : dfsResult) {
            System.out.print(vertex + " ");
        }
        System.out.println();

        List<Integer> bfsResult = graph.bfsTraversal(0);
        System.out.print("BFS обход начиная с вершины 0: ");
        for (int vertex : bfsResult) {
            System.out.print(vertex + " ");
        }
        System.out.println();

        // Алгоритм Дейкстры
        System.out.println("\n=== АЛГОРИТМ ДЕЙКСТРЫ ===");
        int startVertex = 0;
        int[] distances = graph.dijkstra(startVertex);

        System.out.println("Кратчайшие расстояния от вершины " + startVertex + ":");
        for (int i = 0; i < distances.length; i++) {
            if (distances[i] == Integer.MAX_VALUE) {
                System.out.println("Вершина " + i + ": недостижима");
            } else {
                System.out.println("Вершина " + i + ": " + distances[i]);
            }
        }

        // Поиск конкретного пути
        System.out.println("\n=== ПОИСК КОНКРЕТНЫХ ПУТЕЙ ===");
        int from = 0, to = 6;
        List<Integer> path = graph.findShortestPath(from, to);

        if (!path.isEmpty()) {
            System.out.print("Кратчайший путь от " + from + " до " + to + ": ");
            for (int i = 0; i < path.size(); i++) {
                System.out.print(path.get(i));
                if (i < path.size() - 1) System.out.print(" -> ");
            }
            System.out.println();

            // Вычисление длины пути
            int[] dist = graph.dijkstra(from);
            System.out.println("Длина пути: " + dist[to]);
        } else {
            System.out.println("Путь от " + from + " до " + to + " не найден");
        }
    }
}

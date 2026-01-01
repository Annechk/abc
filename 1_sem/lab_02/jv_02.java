import java.util.*;

public class MultilistExample {
    public static void main(String[] args) {
        // Создание вложенного списка (мультисписка)
        List<List<String>> groups = new ArrayList<>();

        // Добавление внутренних списков
        groups.add(Arrays.asList("Hong", "Ryan"));
        groups.add(Arrays.asList("Andry", "Ross"));
        groups.add(Arrays.asList("Mike", "Smith"));

        System.out.println("Исходный мультисписок: " + groups);

        // Преобразование вложенного списка в плоский список
        List<String> flatList = new ArrayList<>();
        for (List<String> group : groups) {
            flatList.addAll(group); // Добавляем все элементы внутреннего списка
        }

        System.out.println("Плоский список: " + flatList);
    }
}


public class QueueExample {
    public static void main(String[] args) {
        // Создание очереди (реализация через LinkedList)
        Queue<String> queue = new LinkedList<>();

        // Добавление элементов в очередь (в конец)
        queue.add("Task 1");
        queue.offer("Task 2"); // альтернативный метод добавления
        queue.add("Task 3");

        System.out.println("Очередь: " + queue);

        // Обработка элементов в порядке FIFO (First-In-First-Out)
        while (!queue.isEmpty()) {
            String current = queue.poll(); // Извлечение и удаление первого элемента
            System.out.println("Обрабатывается: " + current);
        }
    }
}


public class DequeExample {
    public static void main(String[] args) {
        // Создание двусторонней очереди (реализация через ArrayDeque)
        Deque<String> deque = new ArrayDeque<>();

        // Добавление элементов в начало и конец
        deque.addFirst("First"); // Добавить в начало
        deque.addLast("Middle"); // Добавить в конец
        deque.offerFirst("Very First"); // Альтернативный метод добавления в начало
        deque.offerLast("Last"); // Альтернативный метод добавления в конец

        System.out.println("Дек: " + deque);

        // Извлечение элементов с обоих концов
        System.out.println("Первый элемент: " + deque.getFirst());
        System.out.println("Последний элемент: " + deque.getLast());

        // Удаление элементов
        while (!deque.isEmpty()) {
            String element = deque.pollFirst(); // Удаление с начала
            System.out.println("Извлечен: " + element);
        }
    }
}

import java.util.*;

// Класс для демонстрации приоритетной очереди с пользовательскими объектами
class Task {
    private int id;
    private String name;
    private int priority;

    public Task(int id, String name, int priority) {
        this.id = id;
        this.name = name;
        this.priority = priority;
    }

    public int getId() { return id; }
    public String getName() { return name; }
    public int getPriority() { return priority; }

    @Override
    public String toString() {
        return String.format("Task[id=%d, name='%s', priority=%d]", id, name, priority);
    }
}

public class PriorityQueueExample {
    public static void main(String[] args) {
        // Приоритетная очередь с натуральным порядком (для целых чисел - min-heap)
        PriorityQueue<Integer> intQueue = new PriorityQueue<>();
        intQueue.offer(30);
        intQueue.offer(10);
        intQueue.offer(20);

        System.out.println("Целочисленная приоритетная очередь (min-heap):");
        while (!intQueue.isEmpty()) {
            System.out.println(intQueue.poll()); // Выведет: 10, 20, 30
        }

        // Приоритетная очередь с пользовательскими объектами и компаратором
        // Компаратор для сортировки по приоритету (высокий приоритет первый)
        Comparator<Task> priorityComparator = Comparator
            .comparingInt(Task::getPriority)
            .reversed(); // Для порядка от высокого к низкому приоритету

        PriorityQueue<Task> taskQueue = new PriorityQueue<>(priorityComparator);

        // Добавление задач с разными приоритетами
        taskQueue.offer(new Task(1, "Низкий приоритет", 3));
        taskQueue.offer(new Task(2, "Высокий приоритет", 1));
        taskQueue.offer(new Task(3, "Средний приоритет", 2));

        System.out.println("\nПриоритетная очередь задач:");
        while (!taskQueue.isEmpty()) {
            System.out.println(taskQueue.poll()); // Обработаются в порядке приоритета
        }
    }
}

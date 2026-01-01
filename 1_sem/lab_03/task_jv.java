//бинарная_биноминальная куча
import java.util.*;

class BinaryHeap {
    private List<Integer> heap;

    public BinaryHeap() {
        heap = new ArrayList<>();
    }

    public void insert(int key) {
        // Вставка элемента в кучу
        heap.add(key);
        heapifyUp(heap.size() - 1);
    }

    public Integer extractMin() {
        // Извлечение минимального элемента
        if (heap.isEmpty()) return null;

        int minVal = heap.get(0);
        heap.set(0, heap.get(heap.size() - 1));
        heap.remove(heap.size() - 1);
        heapifyDown(0);
        return minVal;
    }

    private void heapifyUp(int index) {
        // Восстановление свойства кучи снизу вверх
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (heap.get(index) < heap.get(parent)) {
            Collections.swap(heap, index, parent);
            heapifyUp(parent);
        }
    }

    private void heapifyDown(int index) {
        // Восстановление свойства кучи сверху вниз
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap.size() && heap.get(left) < heap.get(smallest))
            smallest = left;
        if (right < heap.size() && heap.get(right) < heap.get(smallest))
            smallest = right;

        if (smallest != index) {
            Collections.swap(heap, index, smallest);
            heapifyDown(smallest);
        }
    }

    public boolean isEmpty() {
        return heap.isEmpty();
    }
}

//биноминальная куча
class BinomialTree {
    int key;
    List<BinomialTree> children;
    int order;

    public BinomialTree(int key) {
        this.key = key;
        this.children = new ArrayList<>();
        this.order = 0;
    }

    public void addChild(BinomialTree child) {
        // Добавление дочернего дерева
        children.add(child);
        order++;
    }
}

class BinomialHeap {
    private List<BinomialTree> trees;

    public BinomialHeap() {
        trees = new ArrayList<>();
    }

    public void insert(int key) {
        // Вставка элемента в биномиальную кучу
        BinomialHeap newHeap = new BinomialHeap();
        BinomialTree newTree = new BinomialTree(key);
        newHeap.trees.add(newTree);
        union(newHeap);
    }

    public void union(BinomialHeap other) {
        // Объединение двух биномиальных куч
        trees.addAll(other.trees);
        trees.sort((a, b) -> Integer.compare(a.order, b.order));
        consolidate();
    }

    private void consolidate() {
        // Уплотнение кучи после объединения
        int i = 0;
        while (i < trees.size() - 1) {
            BinomialTree current = trees.get(i);
            BinomialTree next = trees.get(i + 1);

            if (current.order == next.order) {
                if (current.key <= next.key) {
                    current.addChild(next);
                    trees.remove(i + 1);
                } else {
                    next.addChild(current);
                    trees.set(i, next);
                    trees.remove(i + 1);
                }
            } else {
                i++;
            }
        }
    }

    public Integer getMin() {
        // Получение минимального элемента
        if (trees.isEmpty()) return null;

        int minVal = trees.get(0).key;
        for (BinomialTree tree : trees) {
            if (tree.key < minVal)
                minVal = tree.key;
        }
        return minVal;
    }
}

//фибоначчи
class FibonacciHeap {
    static class Node {
        int key;
        int degree;
        boolean marked;
        Node parent;
        Node child;
        Node left;
        Node right;

        Node(int key) {
            this.key = key;
            this.degree = 0;
            this.marked = false;
            this.parent = null;
            this.child = null;
            this.left = this;
            this.right = this;
        }
    }

    private Node minNode;
    private int count;

    public FibonacciHeap() {
        minNode = null;
        count = 0;
    }

    public Node insert(int key) {
        // Вставка элемента в кучу Фибоначчи
        Node node = new Node(key);
        addToRootList(node);

        if (minNode == null || key < minNode.key) {
            minNode = node;
        }

        count++;
        return node;
    }

    private void addToRootList(Node node) {
        // Добавление узла в корневой список
        if (minNode == null) {
            minNode = node;
        } else {
            node.left = minNode;
            node.right = minNode.right;
            minNode.right.left = node;
            minNode.right = node;
        }
    }

    public Integer extractMin() {
        // Извлечение минимального элемента
        if (minNode == null) return null;

        Node minNodePtr = minNode;
        int minValue = minNodePtr.key;

        // Добавляем детей minNode в корневой список
        if (minNodePtr.child != null) {
            Node child = minNodePtr.child;
            do {
                Node nextChild = child.right;
                addToRootList(child);
                child.parent = null;
                child = nextChild;
            } while (child != minNodePtr.child);
        }

        // Удаляем minNode из корневого списка
        minNodePtr.left.right = minNodePtr.right;
        minNodePtr.right.left = minNodePtr.left;

        if (minNodePtr == minNodePtr.right) {
            minNode = null;
        } else {
            minNode = minNodePtr.right;
            consolidate();
        }

        count--;
        return minValue;
    }

    private void consolidate() {
        // Уплотнение кучи Фибоначчи
        if (minNode == null) return;

        Map<Integer, Node> degreeTable = new HashMap<>();
        List<Node> nodes = new ArrayList<>();
        Node current = minNode;

        // Собираем все корневые узлы
        do {
            nodes.add(current);
            current = current.right;
        } while (current != minNode);

        for (Node node : nodes) {
            int degree = node.degree;
            while (degreeTable.containsKey(degree)) {
                Node other = degreeTable.get(degree);
                if (node.key > other.key) {
                    Node temp = node;
                    node = other;
                    other = temp;
                }
                link(other, node);
                degreeTable.remove(degree);
                degree++;
            }
            degreeTable.put(degree, node);
        }

        // Восстанавливаем minNode
        minNode = null;
        for (Node node : degreeTable.values()) {
            if (minNode == null || node.key < minNode.key) {
                minNode = node;
            }
        }
    }

    private void link(Node child, Node parent) {
        // Связывание двух деревьев
        child.left.right = child.right;
        child.right.left = child.left;

        child.parent = parent;
        if (parent.child == null) {
            parent.child = child;
            child.left = child;
            child.right = child;
        } else {
            child.left = parent.child;
            child.right = parent.child.right;
            parent.child.right.left = child;
            parent.child.right = child;
        }

        parent.degree++;
        child.marked = false;
    }

    public boolean isEmpty() {
        return minNode == null;
    }
}

//хеш-таблицы
class HashTable<K, V> {
    private List<List<Pair<K, V>>> table;
    private int size;

    private static class Pair<K, V> {
        K key;
        V value;

        Pair(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    public HashTable(int size) {
        this.size = size;
        this.table = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            table.add(new ArrayList<>());
        }
    }

    public HashTable() {
        this(10);
    }

    private int hash(K key) {
        // Хеш-функция
        return Math.abs(key.hashCode()) % size;
    }

    public void put(K key, V value) {
        // Добавление пары ключ-значение
        int index = hash(key);
        List<Pair<K, V>> bucket = table.get(index);

        // Проверяем, существует ли уже ключ
        for (Pair<K, V> pair : bucket) {
            if (pair.key.equals(key)) {
                pair.value = value;
                return;
            }
        }

        // Добавляем новую пару
        bucket.add(new Pair<>(key, value));
    }

    public V get(K key) {
        // Получение значения по ключу
        int index = hash(key);
        List<Pair<K, V>> bucket = table.get(index);

        for (Pair<K, V> pair : bucket) {
            if (pair.key.equals(key)) {
                return pair.value;
            }
        }

        throw new NoSuchElementException("Key not found");
    }

    public void remove(K key) {
        // Удаление пары ключ-значение
        int index = hash(key);
        List<Pair<K, V>> bucket = table.get(index);

        for (Iterator<Pair<K, V>> iterator = bucket.iterator(); iterator.hasNext();) {
            Pair<K, V> pair = iterator.next();
            if (pair.key.equals(key)) {
                iterator.remove();
                return;
            }
        }

        throw new NoSuchElementException("Key not found");
    }

    public boolean contains(K key) {
        // Проверка наличия ключа
        try {
            get(key);
            return true;
        } catch (NoSuchElementException e) {
            return false;
        }
    }
}

//хеш-таблица с двойным хешированием
class DoubleHashingHashTable<K, V> {
    private static class Entry<K, V> {
        K key;
        V value;
        boolean occupied;
        boolean deleted;

        Entry() {
            occupied = false;
            deleted = false;
        }
    }

    private Entry<K, V>[] table;
    private int size;
    private int count;

    @SuppressWarnings("unchecked")
    public DoubleHashingHashTable(int size) {
        this.size = size;
        this.count = 0;
        this.table = new Entry[size];
        for (int i = 0; i < size; i++) {
            table[i] = new Entry<>();
        }
    }

    private int hash1(K key) {
        // Первая хеш-функция
        return Math.abs(key.hashCode()) % size;
    }

    private int hash2(K key) {
        // Вторая хеш-функция для разрешения коллизий
        return 1 + (Math.abs(key.hashCode()) % (size - 1));
    }

    public void put(K key, V value) {
        // Добавление элемента с двойным хешированием
        if (count >= size) {
            throw new IllegalStateException("Hash table is full");
        }

        int h1 = hash1(key);
        int h2 = hash2(key);

        for (int i = 0; i < size; i++) {
            int index = (h1 + i * h2) % size;
            if (!table[index].occupied || table[index].deleted || table[index].key.equals(key)) {
                table[index].key = key;
                table[index].value = value;
                table[index].occupied = true;
                table[index].deleted = false;
                count++;
                return;
            }
        }

        throw new IllegalStateException("Hash table is full");
    }

    public V get(K key) {
        // Поиск элемента с двойным хешированием
        int h1 = hash1(key);
        int h2 = hash2(key);

        for (int i = 0; i < size; i++) {
            int index = (h1 + i * h2) % size;
            if (!table[index].occupied && !table[index].deleted) {
                break;
            }
            if (table[index].occupied && !table[index].deleted && table[index].key.equals(key)) {
                return table[index].value;
            }
        }

        throw new NoSuchElementException("Key not found");
    }

    public void remove(K key) {
        // Удаление элемента с двойным хешированием
        int h1 = hash1(key);
        int h2 = hash2(key);

        for (int i = 0; i < size; i++) {
            int index = (h1 + i * h2) % size;
            if (!table[index].occupied && !table[index].deleted) {
                break;
            }
            if (table[index].occupied && !table[index].deleted && table[index].key.equals(key)) {
                table[index].deleted = true;
                table[index].occupied = false;
                count--;
                return;
            }
        }

        throw new NoSuchElementException("Key not found");
    }
}

#бинарная_биноминальная куча
class BinaryHeap:
    def __init__(self):
        self.heap = []

    def insert(self, key):
        """Вставка элемента в кучу"""
        self.heap.append(key)
        self._heapify_up(len(self.heap) - 1)

    def extract_min(self):
        """Извлечение минимального элемента"""
        if not self.heap:
            return None
        if len(self.heap) == 1:
            return self.heap.pop()

        min_val = self.heap[0]
        self.heap[0] = self.heap.pop()
        self._heapify_down(0)
        return min_val

    def _heapify_up(self, index):
        """Восстановление свойства кучи снизу вверх"""
        parent = (index - 1) // 2
        if index > 0 and self.heap[index] < self.heap[parent]:
            self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]
            self._heapify_up(parent)

    def _heapify_down(self, index):
        """Восстановление свойства кучи сверху вниз"""
        left = 2 * index + 1
        right = 2 * index + 2
        smallest = index

        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left
        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right

        if smallest != index:
            self.heap[index], self.heap[smallest] = self.heap[smallest], self.heap[index]
            self._heapify_down(smallest)

#биноминальная куча
class BinomialTree:
    def __init__(self, key):
        self.key = key
        self.children = []
        self.order = 0

    def add_child(self, child):
        """Добавление дочернего дерева"""
        self.children.append(child)
        self.order += 1

class BinomialHeap:
    def __init__(self):
        self.trees = []

    def insert(self, key):
        """Вставка элемента в биномиальную кучу"""
        new_heap = BinomialHeap()
        new_tree = BinomialTree(key)
        new_heap.trees.append(new_tree)
        self.union(new_heap)

    def union(self, other):
        """Объединение двух биномиальных куч"""
        self.trees.extend(other.trees)
        self.trees.sort(key=lambda x: x.order)
        self._consolidate()

    def _consolidate(self):
        """Уплотнение кучи после объединения"""
        i = 0
        while i < len(self.trees) - 1:
            if (self.trees[i].order == self.trees[i + 1].order and
                (i + 1 == len(self.trees) - 1 or
                 self.trees[i].order != self.trees[i + 2].order)):

                if self.trees[i].key <= self.trees[i + 1].key:
                    self.trees[i].add_child(self.trees[i + 1])
                    self.trees.pop(i + 1)
                else:
                    self.trees[i + 1].add_child(self.trees[i])
                    self.trees[i] = self.trees[i + 1]
                    self.trees.pop(i + 1)
            else:
                i += 1

#фибоначчи
class FibonacciHeap:
    class Node:
        def __init__(self, key):
            self.key = key
            self.degree = 0
            self.marked = False
            self.parent = None
            self.child = None
            self.left = self
            self.right = self

    def __init__(self):
        self.min_node = None
        self.count = 0

    def insert(self, key):
        """Вставка элемента в кучу Фибоначчи"""
        node = self.Node(key)
        if self.min_node is None:
            self.min_node = node
        else:
            self._add_to_root_list(node)
            if key < self.min_node.key:
                self.min_node = node
        self.count += 1
        return node

    def _add_to_root_list(self, node):
        """Добавление узла в корневой список"""
        node.left = self.min_node
        node.right = self.min_node.right
        self.min_node.right.left = node
        self.min_node.right = node

    def extract_min(self):
        """Извлечение минимального элемента"""
        min_node = self.min_node
        if min_node is not None:
            # Добавляем детей min_node в корневой список
            if min_node.child is not None:
                child = min_node.child
                while True:
                    next_child = child.right
                    self._add_to_root_list(child)
                    child.parent = None
                    child = next_child
                    if child == min_node.child:
                        break

            # Удаляем min_node из корневого списка
            min_node.left.right = min_node.right
            min_node.right.left = min_node.left

            if min_node == min_node.right:
                self.min_node = None
            else:
                self.min_node = min_node.right
                self._consolidate()

            self.count -= 1
        return min_node.key if min_node else None

    def _consolidate(self):
        """Уплотнение кучи Фибоначчи"""
        if self.min_node is None:
            return

        degree_table = {}
        nodes = []
        current = self.min_node

        # Собираем все корневые узлы
        while True:
            nodes.append(current)
            current = current.right
            if current == self.min_node:
                break

        for node in nodes:
            degree = node.degree
            while degree in degree_table:
                other = degree_table[degree]
                if node.key > other.key:
                    node, other = other, node
                self._link(other, node)
                del degree_table[degree]
                degree += 1
            degree_table[degree] = node

        # Восстанавливаем min_node
        self.min_node = None
        for node in degree_table.values():
            if self.min_node is None:
                self.min_node = node
            else:
                if node.key < self.min_node.key:
                    self.min_node = node

    def _link(self, child, parent):
        """Связывание двух деревьев"""
        # Удаляем child из корневого списка
        child.left.right = child.right
        child.right.left = child.left

        # Делаем child дочерним узлом parent
        child.parent = parent
        if parent.child is None:
            parent.child = child
            child.left = child
            child.right = child
        else:
            child.left = parent.child
            child.right = parent.child.right
            parent.child.right.left = child
            parent.child.right = child

        parent.degree += 1
        child.marked = False

#хеш-таблицы
class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, key):
        """Хеш-функция с обработкой строк и чисел"""
        if isinstance(key, str):
            hash_val = 0
            for char in key:
                hash_val = (hash_val * 31 + ord(char)) % self.size
            return hash_val
        else:
            return hash(key) % self.size

    def put(self, key, value):
        """Добавление пары ключ-значение"""
        index = self._hash(key)
        bucket = self.table[index]

        # Проверяем, существует ли уже ключ
        for i, (k, v) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, value)
                return

        # Добавляем новую пару
        bucket.append((key, value))

    def get(self, key):
        """Получение значения по ключу"""
        index = self._hash(key)
        bucket = self.table[index]

        for k, v in bucket:
            if k == key:
                return v
        raise KeyError(f"Key {key} not found")

    def remove(self, key):
        """Удаление пары ключ-значение"""
        index = self._hash(key)
        bucket = self.table[index]

        for i, (k, v) in enumerate(bucket):
            if k == key:
                del bucket[i]
                return
        raise KeyError(f"Key {key} not found")

    def __contains__(self, key):
        """Проверка наличия ключа"""
        try:
            self.get(key)
            return True
        except KeyError:
            return False

#хеш-таблица с двойным хешированием
class DoubleHashingHashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * size
        self.deleted = object()  # Маркер для удаленных элементов

    def _hash1(self, key):
        """Первая хеш-функция"""
        return hash(key) % self.size

    def _hash2(self, key):
        """Вторая хеш-функция для разрешения коллизий"""
        return 1 + (hash(key) % (self.size - 1))

    def put(self, key, value):
        """Добавление элемента с двойным хешированием"""
        hash1 = self._hash1(key)
        hash2 = self._hash2(key)

        for i in range(self.size):
            index = (hash1 + i * hash2) % self.size
            if (self.table[index] is None or
                self.table[index] == self.deleted or
                self.table[index][0] == key):
                self.table[index] = (key, value)
                return

        raise Exception("Hash table is full")

    def get(self, key):
        """Поиск элемента с двойным хешированием"""
        hash1 = self._hash1(key)
        hash2 = self._hash2(key)

        for i in range(self.size):
            index = (hash1 + i * hash2) % self.size
            if self.table[index] is None:
                break
            if (self.table[index] != self.deleted and
                self.table[index][0] == key):
                return self.table[index][1]

        raise KeyError(f"Key {key} not found")

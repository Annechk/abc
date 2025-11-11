from collections import deque

# Класс вершины дерева
class TreeNode:
    def __init__(self, value):
        self.val = value
        self.left = None
        self.right = None

# Класс бинарного дерева
class BinaryTree:
    def __init__(self):
        self.root = None

    # Вставка элемента (нерекурсивная)
    def insert(self, value):
        new_node = TreeNode(value)

        if self.root is None:
            self.root = new_node
            return

        current = self.root
        parent = None

        while current is not None:
            parent = current
            if value < current.val:
                current = current.left
            elif value > current.val:
                current = current.right
            else:
                return  # Значение уже существует

        if value < parent.val:
            parent.left = new_node
        else:
            parent.right = new_node

    # Рекурсивный поиск пути
    def _find_path(self, node, target, path):
        if node is None:
            return False

        path.append(node.val)

        if node.val == target:
            return True

        if (self._find_path(node.left, target, path) or
            self._find_path(node.right, target, path)):
            return True

        path.pop()
        return False

    # Поиск пути от корня до заданного узла
    def find_path_to_node(self, target):
        path = []
        self._find_path(self.root, target, path)
        return path

    # Поиск элемента
    def search(self, value):
        current = self.root
        while current is not None:
            if value == current.val:
                return True
            elif value < current.val:
                current = current.left
            else:
                current = current.right
        return False

    # Рекурсивный обход в глубину
    def _dfs(self, node, result):
        if node is None:
            return
        result.append(node.val)
        self._dfs(node.left, result)
        self._dfs(node.right, result)

    def dfs_traversal(self):
        result = []
        self._dfs(self.root, result)
        return result

    # Обход в ширину
    def bfs_traversal(self):
        result = []
        if self.root is None:
            return result

        queue = deque([self.root])

        while queue:
            current = queue.popleft()
            result.append(current.val)

            if current.left is not None:
                queue.append(current.left)
            if current.right is not None:
                queue.append(current.right)

        return result

    # Вывод дерева
    def print_tree(self):
        print("DFS обход:", self.dfs_traversal())
        print("BFS обход:", self.bfs_traversal())

# Демонстрация работы с деревом
if __name__ == "__main__":
    tree = BinaryTree()

    # Вставка элементов
    values = [8, 3, 10, 1, 6, 14, 4, 7, 13]
    for val in values:
        tree.insert(val)

    print("Бинарное дерево поиска:")
    tree.print_tree()

    # Поиск путей
    targets = [7, 13, 5]
    for target in targets:
        path = tree.find_path_to_node(target)
        if path:
            print(f"Путь к {target}: {path}")
        else:
            print(f"Элемент {target} не найден в дереве")

    # Поиск элементов
    print("Поиск элементов:")
    print(f"Элемент 6: {'найден' if tree.search(6) else 'не найден'}")
    print(f"Элемент 15: {'найден' if tree.search(15) else 'не найден'}")

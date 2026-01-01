import java.util.*;

// Класс вершины дерева
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    public TreeNode(int value) {
        this.val = value;
        this.left = null;
        this.right = null;
    }
}

// Класс бинарного дерева
class BinaryTree {
    private TreeNode root;

    public BinaryTree() {
        this.root = null;
    }

    // Вставка элемента (нерекурсивная)
    public void insert(int value) {
        TreeNode newNode = new TreeNode(value);

        if (root == null) {
            root = newNode;
            return;
        }

        TreeNode current = root;
        TreeNode parent = null;

        while (current != null) {
            parent = current;
            if (value < current.val) {
                current = current.left;
            } else if (value > current.val) {
                current = current.right;
            } else {
                return; // Значение уже существует
            }
        }

        if (value < parent.val) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }
    }

    // Рекурсивный поиск пути
    private boolean findPath(TreeNode node, int target, List<Integer> path) {
        if (node == null) return false;

        path.add(node.val);

        if (node.val == target) return true;

        if (findPath(node.left, target, path) || findPath(node.right, target, path)) {
            return true;
        }

        path.remove(path.size() - 1);
        return false;
    }

    // Поиск пути от корня до заданного узла
    public List<Integer> findPathToNode(int target) {
        List<Integer> path = new ArrayList<>();
        findPath(root, target, path);
        return path;
    }

    // Поиск элемента
    public boolean search(int value) {
        TreeNode current = root;
        while (current != null) {
            if (value == current.val) {
                return true;
            } else if (value < current.val) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        return false;
    }

    // Рекурсивный обход в глубину
    private void dfs(TreeNode node, List<Integer> result) {
        if (node == null) return;
        result.add(node.val);
        dfs(node.left, result);
        dfs(node.right, result);
    }

    public List<Integer> dfsTraversal() {
        List<Integer> result = new ArrayList<>();
        dfs(root, result);
        return result;
    }

    // Обход в ширину
    public List<Integer> bfsTraversal() {
        List<Integer> result = new ArrayList<>();
        if (root == null) return result;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            result.add(current.val);

            if (current.left != null) queue.offer(current.left);
            if (current.right != null) queue.offer(current.right);
        }

        return result;
    }

    // Вывод дерева
    public void printTree() {
        System.out.print("DFS обход: ");
        List<Integer> dfsResult = dfsTraversal();
        for (int val : dfsResult) {
            System.out.print(val + " ");
        }
        System.out.println();

        System.out.print("BFS обход: ");
        List<Integer> bfsResult = bfsTraversal();
        for (int val : bfsResult) {
            System.out.print(val + " ");
        }
        System.out.println();
    }
}

// Демонстрация работы с деревом
public class Labдерево {
    public static void main(String[] args) {
        BinaryTree tree = new BinaryTree();

        // Вставка элементов
        int[] values = {8, 3, 10, 1, 6, 14, 4, 7, 13};
        for (int val : values) {
            tree.insert(val);
        }

        System.out.println("Бинарное дерево поиска:");
        tree.printTree();

        // Поиск путей
        int[] targets = {7, 13, 5};
        for (int target : targets) {
            List<Integer> path = tree.findPathToNode(target);
            if (!path.isEmpty()) {
                System.out.print("Путь к " + target + ": ");
                for (int val : path) {
                    System.out.print(val + " ");
                }
                System.out.println();
            } else {
                System.out.println("Элемент " + target + " не найден в дереве");
            }
        }

        // Поиск элементов
        System.out.println("Поиск элементов: ");
        System.out.println("Элемент 6: " + (tree.search(6) ? "найден" : "не найден"));
        System.out.println("Элемент 15: " + (tree.search(15) ? "найден" : "не найден"));
    }
}

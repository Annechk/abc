// Lab(дерево).cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Класс вершины дерева
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева
class BinaryTree {
private:
    TreeNode* root;

    // Рекурсивное удаление дерева
    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Рекурсивный поиск пути
    bool findPath(TreeNode* node, int target, vector<int>& path) {
        if (!node) return false;

        path.push_back(node->val);

        if (node->val == target) return true;

        if (findPath(node->left, target, path) || findPath(node->right, target, path)) {
            return true;
        }

        path.pop_back();
        return false;
    }

    // Рекурсивный обход в глубину
    void dfs(TreeNode* node, vector<int>& result) {
        if (!node) return;
        result.push_back(node->val);
        dfs(node->left, result);
        dfs(node->right, result);
    }

    // Рекурсивный обход в ширину
    void bfs(TreeNode* node, vector<int>& result) {
        if (!node) return;

        queue<TreeNode*> q;
        q.push(node);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            result.push_back(current->val);

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    // Вставка элемента (нерекурсивная)
    void insert(int value) {
        TreeNode* newNode = new TreeNode(value);

        if (!root) {
            root = newNode;
            return;
        }

        TreeNode* current = root;
        TreeNode* parent = nullptr;

        while (current) {
            parent = current;
            if (value < current->val) {
                current = current->left;
            } else if (value > current->val) {
                current = current->right;
            } else {
                delete newNode; // Значение уже существует
                return;
            }
        }

        if (value < parent->val) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    // Поиск пути от корня до заданного узла
    vector<int> findPathToNode(int target) {
        vector<int> path;
        findPath(root, target, path);
        return path;
    }

    // Поиск элемента
    bool search(int value) {
        TreeNode* current = root;
        while (current) {
            if (value == current->val) {
                return true;
            } else if (value < current->val) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    // Обход в глубину (префиксный)
    vector<int> dfsTraversal() {
        vector<int> result;
        dfs(root, result);
        return result;
    }

    // Обход в ширину
    vector<int> bfsTraversal() {
        vector<int> result;
        bfs(root, result);
        return result;
    }

    // Вывод дерева
    void printTree() {
        cout << "DFS обход: ";
        vector<int> dfsResult = dfsTraversal();
        for (int val : dfsResult) {
            cout << val << " ";
        }
        cout << endl;

        cout << "BFS обход: ";
        vector<int> bfsResult = bfsTraversal();
        for (int val : bfsResult) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// Демонстрация работы с деревом
int main() {
    BinaryTree tree;

    // Вставка элементов
    vector<int> values = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int val : values) {
        tree.insert(val);
    }

    cout << "Бинарное дерево поиска:" << endl;
    tree.printTree();

    // Поиск путей
    vector<int> targets = {7, 13, 5};
    for (int target : targets) {
        vector<int> path = tree.findPathToNode(target);
        if (!path.empty()) {
            cout << "Путь к " << target << ": ";
            for (int val : path) {
                cout << val << " ";
            }
            cout << endl;
        } else {
            cout << "Элемент " << target << " не найден в дереве" << endl;
        }
    }

    // Поиск элементов
    cout << "Поиск элементов: " << endl;
    cout << "Элемент 6: " << (tree.search(6) ? "найден" : "не найден") << endl;
    cout << "Элемент 15: " << (tree.search(15) ? "найден" : "не найден") << endl;

    return 0;
}

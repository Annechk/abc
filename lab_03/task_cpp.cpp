///бинарная_биноминальная куча
#include <vector>
#include <iostream>
using namespace std;

class BinaryHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        // Восстановление свойства кучи снизу вверх
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        // Восстановление свойства кучи сверху вниз
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void insert(int key) {
        // Вставка элемента в кучу
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        // Извлечение минимального элемента
        if (heap.empty()) return -1;

        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return minVal;
    }

    bool empty() const {
        return heap.empty();
    }
};

//биноминальная куча
#include <list>
#include <algorithm>

class BinomialTree {
public:
    int key;
    list<BinomialTree*> children;
    int order;

    BinomialTree(int k) : key(k), order(0) {}

    void addChild(BinomialTree* child) {
        // Добавление дочернего дерева
        children.push_back(child);
        order++;
    }
};

class BinomialHeap {
private:
    list<BinomialTree*> trees;

    void consolidate() {
        // Уплотнение кучи после объединения
        trees.sort([](BinomialTree* a, BinomialTree* b) {
            return a->order < b->order;
        });

        auto it = trees.begin();
        while (it != trees.end() && next(it) != trees.end()) {
            auto current = it;
            auto nextIt = next(it);

            if ((*current)->order == (*nextIt)->order) {
                if ((*current)->key <= (*nextIt)->key) {
                    (*current)->addChild(*nextIt);
                    trees.erase(nextIt);
                } else {
                    (*nextIt)->addChild(*current);
                    *current = *nextIt;
                    trees.erase(nextIt);
                }
            } else {
                ++it;
            }
        }
    }

public:
    void insert(int key) {
        // Вставка элемента в биномиальную кучу
        BinomialHeap newHeap;
        BinomialTree* newTree = new BinomialTree(key);
        newHeap.trees.push_back(newTree);
        unionWith(newHeap);
    }

    void unionWith(BinomialHeap& other) {
        // Объединение двух биномиальных куч
        trees.merge(other.trees);
        consolidate();
    }

    int getMin() {
        // Получение минимального элемента
        if (trees.empty()) return -1;

        int minVal = trees.front()->key;
        for (auto tree : trees) {
            if (tree->key < minVal)
                minVal = tree->key;
        }
        return minVal;
    }
};

//фибоначчи
#include <unordered_map>
#include <cmath>

class FibonacciHeap {
    struct Node {
        int key;
        int degree;
        bool marked;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;

        Node(int k) : key(k), degree(0), marked(false),
            parent(nullptr), child(nullptr),
            left(this), right(this) {}
    };

    Node* minNode;
    int count;

    void addToRootList(Node* node) {
        // Добавление узла в корневой список
        if (minNode == nullptr) {
            minNode = node;
        } else {
            node->left = minNode;
            node->right = minNode->right;
            minNode->right->left = node;
            minNode->right = node;
        }
    }

    void link(Node* child, Node* parent) {
        // Связывание двух деревьев
        child->left->right = child->right;
        child->right->left = child->left;

        child->parent = parent;
        if (parent->child == nullptr) {
            parent->child = child;
            child->left = child;
            child->right = child;
        } else {
            child->left = parent->child;
            child->right = parent->child->right;
            parent->child->right->left = child;
            parent->child->right = child;
        }

        parent->degree++;
        child->marked = false;
    }

    void consolidate() {
        // Уплотнение кучи Фибоначчи
        if (minNode == nullptr) return;

        unordered_map<int, Node*> degreeTable;
        vector<Node*> nodes;
        Node* current = minNode;

        // Собираем все корневые узлы
        do {
            nodes.push_back(current);
            current = current->right;
        } while (current != minNode);

        for (Node* node : nodes) {
            int degree = node->degree;
            while (degreeTable.find(degree) != degreeTable.end()) {
                Node* other = degreeTable[degree];
                if (node->key > other->key) {
                    swap(node, other);
                }
                link(other, node);
                degreeTable.erase(degree);
                degree++;
            }
            degreeTable[degree] = node;
        }

        // Восстанавливаем minNode
        minNode = nullptr;
        for (auto& pair : degreeTable) {
            if (minNode == nullptr || pair.second->key < minNode->key) {
                minNode = pair.second;
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), count(0) {}

    Node* insert(int key) {
        // Вставка элемента в кучу Фибоначчи
        Node* node = new Node(key);
        addToRootList(node);

        if (minNode == nullptr || key < minNode->key) {
            minNode = node;
        }

        count++;
        return node;
    }

    int extractMin() {
        // Извлечение минимального элемента
        if (minNode == nullptr) return -1;

        Node* minNodePtr = minNode;
        int minValue = minNodePtr->key;

        // Добавляем детей minNode в корневой список
        if (minNodePtr->child != nullptr) {
            Node* child = minNodePtr->child;
            do {
                Node* nextChild = child->right;
                addToRootList(child);
                child->parent = nullptr;
                child = nextChild;
            } while (child != minNodePtr->child);
        }

        // Удаляем minNode из корневого списка
        minNodePtr->left->right = minNodePtr->right;
        minNodePtr->right->left = minNodePtr->left;

        if (minNodePtr == minNodePtr->right) {
            minNode = nullptr;
        } else {
            minNode = minNodePtr->right;
            consolidate();
        }

        delete minNodePtr;
        count--;
        return minValue;
    }

    bool empty() const {
        return minNode == nullptr;
    }
};

//хеш-таблицы
#include <functional>
#include <stdexcept>

template<typename K, typename V>
class HashTable {
private:
    vector<list<pair<K, V>>> table;
    size_t size;

    size_t hash(const K& key) const {
        // Хеш-функция
        return hash<K>{}(key) % size;
    }

public:
    HashTable(size_t s = 10) : size(s) {
        table.resize(size);
    }

    void put(const K& key, const V& value) {
        // Добавление пары ключ-значение
        size_t index = hash(key);
        auto& bucket = table[index];

        // Проверяем, существует ли уже ключ
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        // Добавляем новую пару
        bucket.emplace_back(key, value);
    }

    V get(const K& key) const {
        // Получение значения по ключу
        size_t index = hash(key);
        const auto& bucket = table[index];

        for (const auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        throw out_of_range("Key not found");
    }

    void remove(const K& key) {
        // Удаление пары ключ-значение
        size_t index = hash(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }

        throw out_of_range("Key not found");
    }

    bool contains(const K& key) const {
        // Проверка наличия ключа
        try {
            get(key);
            return true;
        } catch (const out_of_range&) {
            return false;
        }
    }
};

//хеш-таблица с двойным хешированием
template<typename K, typename V>
class DoubleHashingHashTable {
private:
    struct Entry {
        K key;
        V value;
        bool occupied;
        bool deleted;

        Entry() : occupied(false), deleted(false) {}
    };

    vector<Entry> table;
    size_t size;
    size_t count;

    size_t hash1(const K& key) const {
        // Первая хеш-функция
        return hash<K>{}(key) % size;
    }

    size_t hash2(const K& key) const {
        // Вторая хеш-функция для разрешения коллизий
        return 1 + (hash<K>{}(key) % (size - 1));
    }

public:
    DoubleHashingHashTable(size_t s = 10) : size(s), count(0) {
        table.resize(size);
    }

    void put(const K& key, const V& value) {
        // Добавление элемента с двойным хешированием
        if (count >= size) {
            throw overflow_error("Hash table is full");
        }

        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        for (size_t i = 0; i < size; i++) {
            size_t index = (h1 + i * h2) % size;
            if (!table[index].occupied || table[index].deleted || table[index].key == key) {
                table[index].key = key;
                table[index].value = value;
                table[index].occupied = true;
                table[index].deleted = false;
                count++;
                return;
            }
        }

        throw overflow_error("Hash table is full");
    }

    V get(const K& key) const {
        // Поиск элемента с двойным хешированием
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        for (size_t i = 0; i < size; i++) {
            size_t index = (h1 + i * h2) % size;
            if (!table[index].occupied && !table[index].deleted) {
                break;
            }
            if (table[index].occupied && !table[index].deleted && table[index].key == key) {
                return table[index].value;
            }
        }

        throw out_of_range("Key not found");
    }

    void remove(const K& key) {
        // Удаление элемента с двойным хешированием
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        for (size_t i = 0; i < size; i++) {
            size_t index = (h1 + i * h2) % size;
            if (!table[index].occupied && !table[index].deleted) {
                break;
            }
            if (table[index].occupied && !table[index].deleted && table[index].key == key) {
                table[index].deleted = true;
                table[index].occupied = false;
                count--;
                return;
            }
        }

        throw out_of_range("Key not found");
    }
};

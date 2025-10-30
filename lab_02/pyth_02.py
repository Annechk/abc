import heapq
from queue import PriorityQueue
import dataclasses
from typing import Any

def multilist_example():
    """
    Мультисписок (вложенный список) в Python
    """
    # Создание вложенного списка
    groups = [['Hong', 'Ryan'], ['Andry', 'Ross'], ['Mike', 'Smith']]

    print("Исходный мультисписок:", groups)

    # Добавление нового вложенного списка
    groups.append(['Anna', 'John'])
    print("После добавления:", groups)

    # Удаление элемента
    removed = groups.pop(1)  # Удаляем второй список
    print(f"Удален: {removed}")
    print("После удаления:", groups)

    # Изменение элемента
    groups[0][1] = 'Ryan_Modified'
    print("После изменения:", groups)

    # Преобразование вложенного списка в плоский
    # Способ 1: Вложенные циклы
    flat_list = []
    for sublist in groups:
        for item in sublist:
            flat_list.append(item)
    print("Плоский список (способ 1):", flat_list)

    # Способ 2: List comprehension
    flat_list2 = [item for sublist in groups for item in sublist]
    print("Плоский список (способ 2):", flat_list2)

    # Способ 3: Использование extend()
    flat_list3 = []
    for sublist in groups:
        flat_list3.extend(sublist)
    print("Плоский список (способ 3):", flat_list3)

multilist_example()

from queue import Queue
import collections

def queue_example():
    """
    Очередь (FIFO) в Python
    """
    print("\n" + "="*50)
    print("ОЧЕРЕДЬ (QUEUE)")
    print("="*50)

    # Способ 1: Использование queue.Queue (потокобезопасная)
    print("1. Использование queue.Queue:")
    q = Queue()

    # Добавление элементов
    q.put(1)
    q.put(2)
    q.put(3)

    print("Размер очереди:", q.qsize())

    # Обработка элементов в порядке FIFO
    while not q.empty():
        item = q.get()
        print(f"Обрабатывается: {item}")

    # Способ 2: Использование collections.deque как очереди
    print("\n2. Использование deque как очереди:")
    queue_deque = collections.deque()

    # Добавление элементов в конец очереди
    queue_deque.append("Task 1")
    queue_deque.append("Task 2")
    queue_deque.append("Task 3")

    print("Очередь:", list(queue_deque))

    # Обработка элементов (извлечение из начала)
    while queue_deque:
        current = queue_deque.popleft()  # Извлечение слева
        print(f"Выполняется: {current}")

queue_example()

import collections

def deque_example():
    """
    Дек (двусторонняя очередь) в Python
    """
    print("\n" + "="*50)
    print("ДВУСТОРОННЯЯ ОЧЕРЕДЬ (DEQUE)")
    print("="*50)

    # Создание дека
    deq = collections.deque([1, 2, 3])
    print("Исходный дек:", list(deq))

    # Добавление элементов в начало и конец
    deq.append(4)       # Добавить в конец
    deq.appendleft(0)   # Добавить в начало
    deq.extend([5, 6])  # Расширить конец
    deq.extendleft([-1, -2])  # Расширить начало

    print("После добавления элементов:", list(deq))

    # Доступ к элементам
    print("Первый элемент:", deq[0])
    print("Последний элемент:", deq[-1])

    # Удаление элементов с обоих концов
    first = deq.popleft()   # Удалить и вернуть первый элемент
    last = deq.pop()        # Удалить и вернуть последний элемент

    print(f"Удален первый: {first}, последний: {last}")
    print("Дек после удаления:", list(deq))

    # Ротация дека
    print("\nДо ротации:", list(deq))
    deq.rotate(2)  # Сдвиг вправо на 2 позиции
    print("После ротации вправо на 2:", list(deq))
    deq.rotate(-1)  # Сдвиг влево на 1 позицию
    print("После ротации влево на 1:", list(deq))

deque_example()


@dataclasses.dataclass(order=True)
class Task:
    """
    Класс задачи для приоритетной очереди
    """
    priority: int
    name: str = dataclasses.field(compare=False)

    def __str__(self):
        return f"Task(priority={self.priority}, name='{self.name}')"

def priority_queue_example():
    """
    Приоритетная очередь в Python
    """
    print("\n" + "="*50)
    print("ПРИОРИТЕТНАЯ ОЧЕРЕДЬ")
    print("="*50)

    # Способ 1: Использование queue.PriorityQueue (потокобезопасная)
    print("1. Использование queue.PriorityQueue:")
    pq = PriorityQueue()

    # Добавление элементов с приоритетом
    pq.put((2, "mid-priority item"))
    pq.put((1, "high-priority item"))
    pq.put((3, "low-priority item"))

    # Обработка элементов в порядке приоритета
    while not pq.empty():
        priority, item = pq.get()
        print(f"Приоритет {priority}: {item}")

    # Способ 2: Использование heapq (бинарная куча)
    print("\n2. Использование heapq:")
    heap = []

    # Добавление элементов в кучу
    heapq.heappush(heap, (2, "Harry"))
    heapq.heappush(heap, (3, "Charles"))
    heapq.heappush(heap, (1, "Riya"))
    heapq.heappush(heap, (4, "Stacy"))

    print("Куча:", heap)

    # Извлечение элементов в порядке приоритета
    while heap:
        priority, name = heapq.heappop(heap)
        print(f"Обработано: {name} (приоритет: {priority})")

    # Способ 3: Приоритетная очередь с объектами
    print("\n3. Приоритетная очередь с объектами:")
    task_queue = PriorityQueue()

    # Добавление задач
    task_queue.put(Task(3, "Низкий приоритет"))
    task_queue.put(Task(1, "Высокий приоритет"))
    task_queue.put(Task(2, "Средний приоритет"))

    while not task_queue.empty():
        task = task_queue.get()
        print(f"Обработана: {task}")

def advanced_heapq_example():
    """
    Дополнительные примеры с heapq
    """
    print("\n" + "="*50)
    print("ДОПОЛНИТЕЛЬНЫЕ ВОЗМОЖНОСТИ HEAPQ")
    print("="*50)

    # Создание кучи из списка
    numbers = [3, 1, 4, 1, 5, 9, 2, 6]
    heapq.heapify(numbers)
    print("Куча из списка:", numbers)

    # Получение наименьшего элемента без удаления
    smallest = numbers[0]
    print("Наименьший элемент:", smallest)

    # Добавление и одновременное извлечение наименьшего
    new_smallest = heapq.heappushpop(numbers, 0)
    print(f"Новый наименьший: {new_smallest}, куча: {numbers}")

    # Извлечение и добавление нового элемента
    replaced = heapq.heapreplace(numbers, 10)
    print(f"Заменен: {replaced}, куча: {numbers}")

if __name__ == "__main__":
    multilist_example()
    queue_example()
    deque_example()
    priority_queue_example()
    advanced_heapq_example()

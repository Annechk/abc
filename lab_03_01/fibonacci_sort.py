
def fibonacci_search(arr, target):
    """
    Поиск Фибоначчи в отсортированном массиве
    """
    n = len(arr)

    # Инициализируем числа Фибоначчи
    fib_m2 = 0  # F(m-2)
    fib_m1 = 1  # F(m-1)
    fib_m = fib_m2 + fib_m1  # F(m)

    # Находим наименьшее число Фибоначчи, большее или равное n
    while fib_m < n:
        fib_m2 = fib_m1
        fib_m1 = fib_m
        fib_m = fib_m2 + fib_m1

    # Инициализируем переменные для поиска
    offset = -1

    # Пока есть элементы для проверки
    while fib_m > 1:
        # Проверяем, не вышли ли за границы массива
        i = min(offset + fib_m2, n - 1)

        # Если target больше значения в i, ищем в правой части
        if arr[i] < target:
            fib_m = fib_m1
            fib_m1 = fib_m2
            fib_m2 = fib_m - fib_m1
            offset = i

        # Если target меньше значения в i, ищем в левой части
        elif arr[i] > target:
            fib_m = fib_m2
            fib_m1 = fib_m1 - fib_m2
            fib_m2 = fib_m - fib_m1

        # Если нашли target
        else:
            return i

    # Проверяем последний элемент
    if fib_m1 and offset + 1 < n and arr[offset + 1] == target:
        return offset + 1

    # Элемент не найден
    return -1

# Демонстрация работы функции
if __name__ == "__main__":
    # Отсортированный массив для поиска
    numbers = [10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100]
    target = 85

    print("Отсортированный массив для поиска:")
    print(numbers)
    print(f"Ищем элемент: {target}")

    # Вызываем функцию поиска Фибоначчи
    result = fibonacci_search(numbers, target)

    # Выводим результат
    if result != -1:
        print(f"Элемент {target} найден на позиции {result}")
    else:
        print(f"Элемент {target} не найден в массиве")

"""
Пример ввода:
Отсортированный массив для поиска: [10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100]
Ищем элемент: 85

Пример вывода:
Элемент 85 найден на позиции 8
"""
```

def bucket_sort(arr):
    if len(arr) == 0:
        return arr

    # Находим минимальное и максимальное значения
    min_val = min(arr)
    max_val = max(arr)

    # Создаем пустые блоки
    bucket_count = len(arr)
    buckets = [[] for _ in range(bucket_count)]

    # Распределяем элементы по блокам
    for num in arr:
        # Вычисляем индекс блока
        index = int((num - min_val) / (max_val - min_val) * (bucket_count - 1))
        buckets[index].append(num)

    # Сортируем каждый блок и объединяем результат
    result = []
    for bucket in buckets:
        result.extend(sorted(bucket))

    return result

# Пример сортировки
if __name__ == "__main__":
    array = [0.42, 0.32, 0.33, 0.52, 0.37, 0.47, 0.51]
    print("Исходный массив:", array)
    sorted_array = bucket_sort(array)
    print("Отсортированный массив:", sorted_array)

"""
Исходный массив: [0.42, 0.32, 0.33, 0.52, 0.37, 0.47, 0.51]
Отсортированный массив: [0.32, 0.33, 0.37, 0.42, 0.47, 0.51, 0.52]
"""

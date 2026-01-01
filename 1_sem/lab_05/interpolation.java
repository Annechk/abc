
public class InterpolationSearch {

    public static int interpolationSearch(int[] arr, int target) {
        /**
         * Интерполирующий поиск в отсортированном массиве
         */
        int low = 0;                    // Нижняя граница поиска
        int high = arr.length - 1;      // Верхняя граница поиска

        // Пока целевой элемент находится в пределах границ и границы не пересеклись
        while (low <= high && target >= arr[low] && target <= arr[high]) {
            // Если границы совпали
            if (low == high) {
                if (arr[low] == target) {
                    return low;  // Возвращаем индекс, если элемент найден
                }
                return -1;  // Элемент не найден
            }

            // Вычисляем позицию с помощью интерполяционной формулы
            int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);

            // Если нашли целевой элемент
            if (arr[pos] == target) {
                return pos;  // Возвращаем индекс элемента
            }

            // Если целевой элемент меньше элемента в вычисленной позиции
            if (arr[pos] > target) {
                high = pos - 1;  // Ищем в левой части
            }
            // Если целевой элемент больше элемента в вычисленной позиции
            else {
                low = pos + 1;   // Ищем в правой части
            }
        }

        // Элемент не найден
        return -1;
    }

    // Демонстрация работы функции
    public static void main(String[] args) {
        // Отсортированный массив с равномерным распределением
        int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        int target = 60;

        System.out.println("Отсортированный массив для поиска:");
        printArray(numbers);
        System.out.println("Ищем элемент: " + target);

        // Вызываем функцию интерполирующего поиска
        int result = interpolationSearch(numbers, target);

        // Выводим результат
        if (result != -1) {
            System.out.println("Элемент " + target + " найден на позиции " + result);
        } else {
            System.out.println("Элемент " + target + " не найден в массиве");
        }
    }

    // Вспомогательная функция для вывода массива
    private static void printArray(int[] arr) {
        for (int value : arr) {
            System.out.print(value + " ");
        }
        System.out.println();
    }
}

/*
Пример ввода:
Отсортированный массив для поиска: 10 20 30 40 50 60 70 80 90 100
Ищем элемент: 60

Пример вывода:
Элемент 60 найден на позиции 5
*/
```

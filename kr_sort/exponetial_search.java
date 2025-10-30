import java.util.Arrays;

public class ExponentialSearch {

    // Функция экспоненциального поиска
    public static int exponentialSearch(int[] arr, int target) {
        int n = arr.length;

        // Проверяем первый элемент
        if (arr[0] == target) {
            return 0;
        }

        // Экспоненциально увеличиваем индекс для определения диапазона
        int i = 1;
        while (i < n && arr[i] <= target) {
            i = i * 2; // Удваиваем шаг на каждой итерации
        }

        // Выполняем бинарный поиск в найденном диапазоне
        return binarySearch(arr, target, i / 2, Math.min(i, n - 1));
    }

    // Вспомогательная функция бинарного поиска
    private static int binarySearch(int[] arr, int target, int left, int right) {
        while (left <= right) {
            // Вычисляем средний индекс
            int mid = left + (right - left) / 2;

            // Если элемент найден
            if (arr[mid] == target) {
                return mid;
            }

            // Сужаем диапазон поиска
            if (arr[mid] < target) {
                left = mid + 1; // Ищем в правой половине
            } else {
                right = mid - 1; // Ищем в левой половине
            }
        }

        // Элемент не найден
        return -1;
    }

    // Основная функция для демонстрации работы
    public static void main(String[] args) {
        // Исходный массив
        int[] array = {2, 5, 8, 12, 16, 23, 38, 45, 67, 89};

        // Вывод исходного массива
        System.out.print("Исходный массив: ");
        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Сортировка массива (требование для экспоненциального поиска)
        Arrays.sort(array);

        // Вывод отсортированного массива
        System.out.print("Отсортированный массив: ");
        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Поиск существующего элемента
        int target = 23;
        int index = exponentialSearch(array, target);
        if (index != -1) {
            System.out.println("Элемент " + target + " найден на позиции " + index);
        } else {
            System.out.println("Элемент " + target + " не найден");
        }

        // Поиск несуществующего элемента
        target = 50;
        index = exponentialSearch(array, target);
        if (index != -1) {
            System.out.println("Элемент " + target + " найден на позиции " + index);
        } else {
            System.out.println("Элемент " + target + " не найден");
        }
    }
}

//Исходный массив: 2 5 8 12 16 23 38 45 67 89
//Отсортированный массив: 2 5 8 12 16 23 38 45 67 89

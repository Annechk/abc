public class HeapSort {

    // Основная функция пирамидальной сортировки
public static void heapSort(int[] arr) {
        int n = arr.length;

        // Построение max-кучи. Перебираем все корневые узлы справа налево
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Извлекаем элементы из кучи один за другим
        for (int i = n - 1; i > 0; i--) {
            // Перемещаем текущий корень (максимальный элемент) в конец
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Вызываем heapify на уменьшенной куче
            heapify(arr, i, 0);
        }
    }

    // Преобразует поддерево в max-кучу
private static void heapify(int[] arr, int n, int i) {
        int largest = i;        // Инициализируем наибольший элемент как корень
        int left = 2 * i + 1;   // Левый дочерний элемент
        int right = 2 * i + 2;  // Правый дочерний элемент

        // Если левый дочерний элемент существует и больше корня
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // Если правый дочерний элемент существует и больше текущего наибольшего
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // Если наибольший элемент не корень
        if (largest != i) {
            // Меняем местами корень с наибольшим дочерним элементом
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            // Рекурсивно преобразуем затронутое поддерево
            heapify(arr, n, largest);
        }
    }

    // Демонстрация работы функции
public static void main(String[] args) {
        int[] array = {64, 34, 25, 12, 22, 11, 90, 5, 77, 18};

        System.out.println("Исходный массив:");
        printArray(array);

        // Вызываем функцию пирамидальной сортировки
        heapSort(array);

        System.out.println("\nОтсортированный массив:");
        printArray(array);
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
Исходный массив: 64 34 25 12 22 11 90 5 77 18

Пример вывода:
Отсортированный массив: 5 11 12 18 22 25 34 64 77 90
*/

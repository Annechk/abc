public class SelectionSort {
    // Метод для сортировки массива выбором
    public static void selectionSort(int[] array) {
        int n = array.length;

        // Проходим по каждому элементу массива
        for (int i = 0; i < n - 1; i++) {
            // Предполагаем, что первый элемент текущего участка является минимальным
            int minIndex = i;

            // Ищем наименьший элемент среди остальных элементов справа
            for (int j = i + 1; j < n; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;   // Обновляем индекс минимального элемента
                }
            }

            // Меняем найденный минимум с первым элементом текущего участка
            swap(array, i, minIndex);
        }
    }

    // Вспомогательная функция для обмена двух элементов в массиве
    private static void swap(int[] arr, int index1, int index2) {
        int temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }

    // Основная программа для проверки сортировки
    public static void main(String[] args) {
        int[] array = {64, 25, 12, 22, 11};

        System.out.println("Исходный массив:");
        printArray(array); // вывод исходного массива

        selectionSort(array); // сортируем массив методом выбора

        System.out.println("\nОтсортированный массив:");
        printArray(array); // вывод отсортированного массива
    }

    // Вспомогательная функция для вывода массива
    private static void printArray(int[] arr) {
        for (int value : arr) {
            System.out.print(value + " ");
        }
    }
}

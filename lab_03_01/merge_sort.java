public class MergeSort {

    // Основная функция сортировки слиянием
    public static void mergeSort(int[] arr) {
        // Если массив пустой или содержит один элемент - он уже отсортирован
        if (arr == null || arr.length <= 1) {
            return;
        }

        // Создаем временный массив для слияния
        int[] temp = new int[arr.length];

        // Вызываем рекурсивную функцию сортировки
        mergeSort(arr, temp, 0, arr.length - 1);
    }

    // Рекурсивная функция сортировки слиянием
    private static void mergeSort(int[] arr, int[] temp, int left, int right) {
        // Базовый случай: если левая граница >= правой, подмассив отсортирован
        if (left >= right) {
            return;
        }

        // Находим середину массива
        int mid = left + (right - left) / 2;

        // Рекурсивно сортируем левую половину
        mergeSort(arr, temp, left, mid);

        // Рекурсивно сортируем правую половину
        mergeSort(arr, temp, mid + 1, right);

        // Сливаем две отсортированные половины
        merge(arr, temp, left, mid, right);
    }

    // Функция для слияния двух отсортированных подмассивов
    private static void merge(int[] arr, int[] temp, int left, int mid, int right) {
        // Копируем элементы во временный массив
        for (int i = left; i <= right; i++) {
            temp[i] = arr[i];
        }

        int i = left;      // Указатель для левого подмассива
        int j = mid + 1;   // Указатель для правого подмассива
        int k = left;      // Указатель для результирующего массива

        // Сливаем два подмассива, выбирая меньший элемент на каждом шаге
        while (i <= mid && j <= right) {
            if (temp[i] <= temp[j]) {
                arr[k] = temp[i];
                i++;
            } else {
                arr[k] = temp[j];
                j++;
            }
            k++;
        }

        // Копируем оставшиеся элементы из левого подмассива (если есть)
        while (i <= mid) {
            arr[k] = temp[i];
            i++;
            k++;
        }

        // Правый подмассив не нужно копировать отдельно,
        // так как его элементы уже на своих местах
    }

    // Демонстрация работы функции
    public static void main(String[] args) {
        int[] array = {64, 34, 25, 12, 22, 11, 90, 5};

        System.out.println("Исходный массив:");
        printArray(array);

        // Вызываем функцию сортировки слиянием
        mergeSort(array);

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

Пример ввода:
Исходный массив: 64 34 25 12 22 11 90 5

Пример вывода:
Отсортированный массив: 5 11 12 22 25 34 64 90
*/
```

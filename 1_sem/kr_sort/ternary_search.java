import java.util.Arrays;

public class TernarySearch {

    // Функция тернарного поиска
    public static int ternarySearch(int[] arr, int target) {
        return ternarySearchRecursive(arr, target, 0, arr.length - 1);
    }

    private static int ternarySearchRecursive(int[] arr, int target, int left, int right) {
        if (left > right) {
            return -1;
        }

        // Вычисляем две точки деления
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        // Проверяем точки деления
        if (arr[mid1] == target) {
            return mid1;
        }
        if (arr[mid2] == target) {
            return mid2;
        }

        // Определяем в какой трети искать
        if (target < arr[mid1]) {
            // Ищем в левой трети
            return ternarySearchRecursive(arr, target, left, mid1 - 1);
        } else if (target > arr[mid2]) {
            // Ищем в правой трети
            return ternarySearchRecursive(arr, target, mid2 + 1, right);
        } else {
            // Ищем в средней трети
            return ternarySearchRecursive(arr, target, mid1 + 1, mid2 - 1);
        }
    }

    public static void main(String[] args) {
        int[] array = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25};

        System.out.print("Исходный массив: ");
        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Массив должен быть отсортирован для тернарного поиска
        Arrays.sort(array);

        System.out.print("Отсортированный массив: ");
        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Поиск существующих элементов
        int target1 = 7;
        int target2 = 19;
        int target3 = 25;

        int index1 = ternarySearch(array, target1);
        int index2 = ternarySearch(array, target2);
        int index3 = ternarySearch(array, target3);

        System.out.println("Элемент " + target1 + " найден на позиции: " + index1);
        System.out.println("Элемент " + target2 + " найден на позиции: " + index2);
        System.out.println("Элемент " + target3 + " найден на позиции: " + index3);

        // Поиск несуществующего элемента
        int target4 = 8;
        int index4 = ternarySearch(array, target4);
        System.out.println("Элемент " + target4 + " найден на позиции: " + index4);
    }
}

// Исходный массив: 1 3 5 7 9 11 13 15 17 19 21 23 25
// Отсортированный массив: 1 3 5 7 9 11 13 15 17 19 21 23 25

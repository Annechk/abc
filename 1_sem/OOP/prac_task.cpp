#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    // Поля класса
    string title;
    string author;
    double price;
    int quantity;

public:
    // Конструктор по умолчанию
    Book() {
        title = "Неизвестно";
        author = "Неизвестно";
        price = 0;
        quantity = 0;
        cout << "Конструктор по умолчанию вызван" << endl;
    }

    // Конструктор с параметрами
    Book(string bookTitle, string bookAuthor, double bookPrice, int bookQuantity) {
        title = bookTitle;
        author = bookAuthor;

        // Проверка цены
        if (bookPrice > 0) {
            price = bookPrice;
        } else {
            cout << "Ошибка! Цена должна быть больше 0" << endl;
            price = 0;
        }

        // Проверка количества
        if (bookQuantity >= 0) {
            quantity = bookQuantity;
        } else {
            cout << "Ошибка! Количество не может быть отрицательным" << endl;
            quantity = 0;
        }

        cout << "Конструктор с параметрами вызван" << endl;
    }

    // Деструктор
    ~Book() {
        cout << "Деструктор вызван для книги \"" << title << "\"" << endl;
    }

    // Геттеры
    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    double getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }

    // Сеттеры с валидацией
    void setPrice(double newPrice) {
        if (newPrice > 0) {
            price = newPrice;
            cout << "Цена изменена" << endl;
        } else {
            cout << "Ошибка! Цена должна быть больше 0" << endl;
        }
    }

    void setQuantity(int newQuantity) {
        if (newQuantity >= 0) {
            quantity = newQuantity;
            cout << "Количество изменено" << endl;
        } else {
            cout << "Ошибка! Количество не может быть отрицательным" << endl;
        }
    }

    // Метод продажи экземпляра
    void sellCopy() {
        if (quantity > 0) {
            quantity--;
            cout << "Книга продана. Осталось: " << quantity << " шт." << endl;
        } else {
            cout << "Ошибка! Нет книг в наличии" << endl;
        }
    }

    // Метод продажи нескольких экземпляров
    void sellCopies(int count) {
        if (count <= 0) {
            cout << "Ошибка! Количество должно быть больше 0" << endl;
            return;
        }

        if (quantity >= count) {
            quantity -= count;
            cout << "Продано " << count << " книг. Осталось: " << quantity << " шт." << endl;
        } else {
            cout << "Ошибка! В наличии только " << quantity << " книг" << endl;
        }
    }

    // Метод поступления партии
    void addStock(int count) {
        if (count > 0) {
            quantity += count;
            cout << "Поступило " << count << " книг. Теперь в наличии: " << quantity << " шт." << endl;
        } else {
            cout << "Ошибка! Количество должно быть больше 0" << endl;
        }
    }

    // Метод применения скидки
    void applyDiscount(int percent) {
        if (percent <= 0) {
            cout << "Ошибка! Процент скидки должен быть больше 0" << endl;
            return;
        }

        if (percent > 100) {
            cout << "Ошибка! Процент скидки не может быть больше 100" << endl;
            return;
        }

        double discount = price * percent / 100;
        price = price - discount;
        cout << "Применена скидка " << percent << "%. Новая цена: " << price << " руб." << endl;
    }

    // Метод проверки наличия
    bool isAvailable() {
        return quantity > 0;
    }

    // Метод вывода информации
    void printInfo() {
        cout << "\n--- Информация о книге ---" << endl;
        cout << "Название: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "Цена: " << price << " руб." << endl;
        cout << "В наличии: " << quantity << " шт." << endl;
        cout << "Статус: ";
        if (isAvailable()) {
            cout << "есть в наличии";
        } else {
            cout << "нет в наличии";
        }
        cout << "\n--------------------------\n" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Работа с классом Book ===\n" << endl;

    // Создание объектов
    cout << "--- Создание объектов ---" << endl;
    Book book1;
    Book book2("Война и мир", "Лев Толстой", 500, 10);
    cout << endl;

    // Демонстрация геттеров
    cout << "--- Геттеры ---" << endl;
    cout << "Книга 2:" << endl;
    cout << "Название: " << book2.getTitle() << endl;
    cout << "Автор: " << book2.getAuthor() << endl;
    cout << "Цена: " << book2.getPrice() << endl;
    cout << "Количество: " << book2.getQuantity() << endl;
    cout << endl;

    // Демонстрация сеттеров с валидацией
    cout << "--- Сеттеры с валидацией ---" << endl;
    cout << "Пытаемся установить цену -100:" << endl;
    book1.setPrice(-100);

    cout << "\nПытаемся установить количество -5:" << endl;
    book1.setQuantity(-5);

    cout << "\nУстанавливаем корректные значения:" << endl;
    book1.setPrice(300);
    book1.setQuantity(5);
    cout << endl;

    // Демонстрация методов
    cout << "--- Метод продажи ---" << endl;
    cout << "Исходное количество book2: " << book2.getQuantity() << endl;
    book2.sellCopy();
    book2.sellCopies(3);
    book2.sellCopies(10);
    cout << endl;

    cout << "--- Метод поступления ---" << endl;
    cout << "Исходное количество book1: " << book1.getQuantity() << endl;
    book1.addStock(10);
    book1.addStock(-5);
    cout << endl;

    cout << "--- Метод применения скидки ---" << endl;
    cout << "Исходная цена book2: " << book2.getPrice() << endl;
    book2.applyDiscount(20);
    book2.applyDiscount(150);
    book2.applyDiscount(-10);
    cout << endl;

    // Демонстрация printInfo
    cout << "--- Вывод информации ---" << endl;
    book1.printInfo();
    book2.printInfo();

    // Демонстрация валидации в конструкторе
    cout << "--- Валидация в конструкторе ---" << endl;
    Book book3("", "", -100, -5);
    book3.printInfo();

    cout << "\n=== Завершение программы ===" << endl;

    return 0;
}

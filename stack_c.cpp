#include <iostream>
#include <stack>
#include <string>

int main()
{
    // Создаем пустой список с названием users
    std::stack<std::string> users;

    // Добавляем элементы
    users.push("Tom");
    users.push("Sam");
    users.push("Bob");
    users.push("Alisa");
    users.push("Kate");
    users.push("Lana");

    // Выводим элементы
    while (!users.empty())
    {
        std::cout << users.top() << std::endl;
        // Удаляем после вывода элемента
        users.pop();
    }

    return 0;
}

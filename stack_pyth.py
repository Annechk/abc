# Создаем стек
stack = []

# Добавляем элементы
stack.append('a')
stack.append('b')
stack.append('c')

# Выводим элементы
print(stack)

# Удаляем элементы
while not stack.is_empty():
    print(stack.pop())

public class Main
{
    public static void main(String[] args)
    {
        // Cоздаем стек
        MyStack<Integer> stack = new MyStack<>(10);

        // Добавляем элементы
        stack.push(5);
        stack.push(10);
        stack.push(15);

        System.out.println("Вершина стека: " + stack.peek());

        // Вывод все элементы стека
        stack.printStack();

        // Удаляем все элементы
        while (!stack.isEmpty())
        {
            System.out.println(stack.pop());
        }
    }
}

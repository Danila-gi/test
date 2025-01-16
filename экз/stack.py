class Stack:
    def __init__(self):
        self.items = []  # Используем список для хранения элементов стека

    def push(self, item):
        """Добавляет элемент на вершину стека."""
        self.items.append(item)

    def pop(self):
        """Удаляет и возвращает элемент с вершины стека."""
        if self.is_empty():
            raise IndexError("Стек пуст")
        return self.items.pop()  # Удаляем последний элемент

    def is_empty(self):
        """Проверяет, пуст ли стек."""
        return len(self.items) == 0

    def size(self):
        """Возвращает количество элементов в стеке."""
        return len(self.items)

    def peek(self):
        """Возвращает элемент с вершины стека без его удаления."""
        if self.is_empty():
            raise IndexError("Стек пуст")
        return self.items[-1]

    def __str__(self):
        """Возвращает строковое представление стека."""
        return str(self.items)
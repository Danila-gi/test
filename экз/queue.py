class Queue:
    def __init__(self):
        self.items = []  # Используем список для хранения элементов очереди

    def enqueue(self, item):
        """Добавляет элемент в конец очереди."""
        self.items.append(item)

    def dequeue(self):
        """Удаляет и возвращает элемент из начала очереди."""
        if self.is_empty():
            raise IndexError("Очередь пуста")
        return self.items.pop(0)  # Удаляем первый элемент

    def is_empty(self):
        """Проверяет, пуста ли очередь."""
        return len(self.items) == 0

    def size(self):
        """Возвращает количество элементов в очереди."""
        return len(self.items)

    def peek(self):
        """Возвращает элемент из начала очереди без его удаления."""
        if self.is_empty():
            raise IndexError("Очередь пуста")
        return self.items[0]

    def __str__(self):
        """Возвращает строковое представление очереди."""
        return str(self.items)
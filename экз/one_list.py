class Node:
    """Класс для узла односвязного списка."""
    def __init__(self, data):
        self.data = data  # Данные узла
        self.next = None  # Ссылка на следующий узел

class SinglyLinkedList:
    """Класс для односвязного списка."""
    def __init__(self):
        self.head = None  # Начало списка

    def is_empty(self):
        """Проверяет, пуст ли список."""
        return self.head is None

    def append(self, data):
        """Добавляет элемент в конец списка."""
        new_node = Node(data)
        if self.is_empty():
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:  # Ищем последний узел
                current = current.next
            current.next = new_node

    def prepend(self, data):
        """Добавляет элемент в начало списка."""
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node

    def insert_at(self, position, data):
        """Вставляет элемент на указанную позицию."""
        if position <= 0:
            # Если позиция меньше или равна 0, добавляем в начало
            self.prepend(data)
            return
        if self.is_empty():
            # Если список пуст, добавляем элемент
            self.append(data)
            return

        # Ищем узел на позиции (position - 1)
        current = self.head
        index = 0
        while current.next is not None and index < position - 1:
            current = current.next
            index += 1

        # Создаем новый узел
        new_node = Node(data)
        new_node.next = current.next
        current.next = new_node

    def delete(self, data):
        """Удаляет первый узел с указанными данными."""
        if self.is_empty():
            raise ValueError("Список пуст")

        # Если удаляемый элемент в начале списка
        if self.head.data == data:
            self.head = self.head.next
            return

        # Ищем узел для удаления
        current = self.head
        while current.next is not None and current.next.data != data:
            current = current.next

        # Если узел найден, удаляем его
        if current.next is not None:
            current.next = current.next.next
        else:
            raise ValueError("Элемент не найден")

    def search(self, data):
        """Проверяет, есть ли элемент в списке."""
        current = self.head
        while current is not None:
            if current.data == data:
                return True
            current = current.next
        return False

    def __str__(self):
        """Возвращает строковое представление списка."""
        elements = []
        current = self.head
        while current is not None:
            elements.append(str(current.data))
            current = current.next
        return " -> ".join(elements)
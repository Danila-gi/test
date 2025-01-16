class Node:
    """Класс для узла двусвязного списка."""
    def __init__(self, data):
        self.data = data  # Данные узла
        self.next = None  # Ссылка на следующий узел
        self.prev = None  # Ссылка на предыдущий узел

class DoublyLinkedList:
    """Класс для двусвязного списка."""
    def __init__(self):
        self.head = None  # Начало списка
        self.tail = None  # Конец списка

    def is_empty(self):
        """Проверяет, пуст ли список."""
        return self.head is None

    def append(self, data):
        """Добавляет элемент в конец списка."""
        new_node = Node(data)
        if self.is_empty():
            # Если список пуст, новый узел становится и головой, и хвостом
            self.head = new_node
            self.tail = new_node
        else:
            # Добавляем новый узел в конец и обновляем хвост
            new_node.prev = self.tail
            self.tail.next = new_node
            self.tail = new_node

    def prepend(self, data):
        """Добавляет элемент в начало списка."""
        new_node = Node(data)
        if self.is_empty():
            # Если список пуст, новый узел становится и головой, и хвостом
            self.head = new_node
            self.tail = new_node
        else:
            # Добавляем новый узел в начало и обновляем голову
            new_node.next = self.head
            self.head.prev = new_node
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
        new_node.prev = current

        if current.next is not None:
            # Если вставляем не в конец, обновляем ссылку на предыдущий узел у следующего узла
            current.next.prev = new_node
        else:
            # Если вставляем в конец, обновляем хвост
            self.tail = new_node

        # Обновляем ссылку на следующий узел у текущего узла
        current.next = new_node

    def delete(self, data):
        """Удаляет первый узел с указанными данными."""
        if self.is_empty():
            raise ValueError("Список пуст")

        # Если удаляемый элемент в начале списка
        if self.head.data == data:
            self.head = self.head.next
            if self.head is not None:
                self.head.prev = None
            else:
                # Если список стал пустым, обновляем хвост
                self.tail = None
            return

        # Если удаляемый элемент в конце списка
        if self.tail.data == data:
            self.tail = self.tail.prev
            self.tail.next = None
            return

        # Ищем узел для удаления
        current = self.head
        while current is not None and current.data != data:
            current = current.next

        # Если узел найден, удаляем его
        if current is not None:
            current.prev.next = current.next
            if current.next is not None:
                current.next.prev = current.prev
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
        return " <-> ".join(elements)
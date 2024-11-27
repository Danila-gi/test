"""Модуль, содержащий хэш-таблицу"""

from tree import AVLTree, Record


class Values_for_group:
    """Класс, содержащий авл-дерево, которое является значение ключа в таблице"""
    def __init__(self, heap: AVLTree):
        """Инициализация данных"""
        self.heap = heap


class HashTable:
    """Класс хэш-таблицы"""
    def __init__(self, size=100):
        """Инициализация данных"""
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, key: int):
        """Хэш-функция"""
        return key % self.size

    def insert(self, key: int, value: Record = None):
        """Вставка записи в группу"""
        if value is None:
            value = AVLTree()
        index = self._hash(key)

        for item in self.table[index]:
            if item[0] == key:
                item[1].insert_record(value)
                return
        self.table[index].append([key, value])

    def find(self, key: int):
        """Нахождение авл-дерева соответствующей группы"""
        index = self._hash(key)
        for item in self.table[index]:
            if item[0] == key:
                return item[1]
        return None

    def remove(self, key: int):
        """Удаление ключа из таблицы"""
        index = self._hash(key)
        for i, item in enumerate(self.table[index]):
            if item[0] == key:
                del self.table[index][i]
                return

    def get_all_keys(self):
        """Вывод всех ключей"""
        all_keys = []
        for bucket in self.table:
            for item in bucket:
                all_keys.append(item[0])
        return all_keys

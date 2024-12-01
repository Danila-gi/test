"""Модуль, содержащий хэш-таблицу"""

from tree import AVLTree, Record


class HashTable:
    """Класс хэш-таблицы"""

    def __init__(self, size=100):
        """Инициализация данных"""
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, key: int):
        """Хэш-функция"""
        return key % self.size

    def add_group(self, key: int):
        """Добавление группы в хэш-таблицу"""
        index = self._hash(key)
        value = AVLTree()

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

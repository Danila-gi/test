class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size  # Инициализируем таблицу
        self.DELETED = object()  # Маркер для удаленных элементов

    def hash_function(self, key):
        """Простая хеш-функция для демонстрации."""
        return hash(key) % self.size

    def insert(self, key, value):
        """Вставляет пару ключ-значение в хеш-таблицу."""
        index = self.hash_function(key)
        i = 0

        # Ищем свободную ячейку
        while self.table[index] is not None and self.table[index] != self.DELETED:
            if self.table[index][0] == key:  # Если ключ уже существует, обновляем значение
                self.table[index] = (key, value)
                return
            i += 1
            index = (self.hash_function(key) + i) % self.size  # Линейное исследование
            # index = (self.hash_function(key) + i**2) % self.size Квадратичное

        # Вставляем элемент
        self.table[index] = (key, value)

    def search(self, key):
        """Ищет значение по ключу."""
        index = self.hash_function(key)
        i = 0

        # Ищем ключ
        while self.table[index] is not None:
            if self.table[index] != self.DELETED and self.table[index][0] == key:
                return self.table[index][1]  # Возвращаем значение
            i += 1
            index = (self.hash_function(key) + i) % self.size  # Линейное исследование

        # Ключ не найден
        return None

    def delete(self, key):
        """Удаляет пару ключ-значение из хеш-таблицы."""
        index = self.hash_function(key)
        i = 0

        # Ищем ключ
        while self.table[index] is not None:
            if self.table[index] != self.DELETED and self.table[index][0] == key:
                self.table[index] = self.DELETED  # Помечаем ячейку как удаленную
                return
            i += 1
            index = (self.hash_function(key) + i) % self.size  # Линейное исследование
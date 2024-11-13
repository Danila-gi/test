from university import University_heap, Node_for_university


class Values_for_student:
    def __init__(self, heap: University_heap, node: Node_for_university):
        self.heap = heap
        self.node = node


class HashTable:
    def __init__(self, size=1000):
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self._hash(key)

        for item in self.table[index]:
            if item[0] == key:
                item[1] = value
                return
        self.table[index].append([key, value])

    def find(self, key):
        index = self._hash(key)
        for item in self.table[index]:
            if item[0] == key:
                return item[1]
        return None

    def remove(self, key):
        index = self._hash(key)
        for i, item in enumerate(self.table[index]):
            if item[0] == key:
                del self.table[index][i]
                return
        print(f"Ключ '{key}' не найден для удаления.")

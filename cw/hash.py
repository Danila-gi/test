from heap import Heap


class Values_for_group:
    def __init__(self, heap: Heap):
        self.heap = heap


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
                item[1].add_node(value)
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

    def get_all_keys(self):
        all_keys = []
        for bucket in self.table:
            for item in bucket:
                all_keys.append(item[0])
        return all_keys

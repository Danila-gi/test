# Макс-куча

class Heap:
    def __init__(self):
        self.heap = []
        self.heap_size = 0

    def heapify_down(self, heap, size, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2

        if left < size and heap[i] < heap[left]:
            largest = left

        if right < size and heap[largest] < heap[right]:
            largest = right

        if largest != i:
            heap[i], heap[largest] = heap[largest], heap[i]
            self.heapify_down(heap, size, largest)

    def sift_up(self, i):
        """Просеивание вверх для узла с индексом i."""
        while i > 0:
            parent = (i - 1) // 2  # Индекс родительского узла
            if self.heap[i] > self.heap[parent]:  # Для max-heap
                self.heap[i], self.heap[parent] = self.heap[parent], self.heap[i]
                i = parent
            else:
                break

    def add_node(self, node):
        if self.heap_size == 0:
            self.heap.append(node)
            self.heap_size += 1
        else:
            self.heap.append(node)
            self.heap_size += 1
            for i in range((self.heap_size // 2) - 1, -1, -1): # можно заменить на self.sift_up(self.heap_size - 1)
                self.heapify_down(self.heap, self.heap_size, i)

    def remove_node(self, node):
        i = 0
        for i in range(0, self.heap_size):
            if node == self.heap[i]:
                break

        self.heap[i], self.heap[self.heap_size - 1] = self.heap[self.heap_size - 1], self.heap[i]
        self.heap.remove(node)
        self.heap_size -= 1

        for i in range((self.heap_size // 2) - 1, -1, -1):
            self.heapify_down(self.heap, self.heap_size, i)

    def extract_max(self):
        if self.heap_size == 0:
            return None

        max_value = self.heap[0]

        self.heap[0] = self.heap[self.heap_size - 1]
        self.heap.pop()
        self.heap_size -= 1

        self.heapify_down(self.heap, self.heap_size, 0)

        return max_value

    def find_node(self, node):
        for record in self.heap:
            if record == node:
                return record
        return None


    def change_value(self, old_value, new_value):
        if old_value not in self.heap:
            raise ValueError("Элемент не найден в куче")

        i = 0
        for i in range(0, self.heap_size):
            if old_value == self.heap[i]:
                break

        self.heap[i] = new_value

        if new_value > old_value:
            self.sift_up(i)
        else:
            self.heapify_down(self.heap, self.heap_size, i)

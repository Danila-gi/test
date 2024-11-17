class Record:
    def __init__(self, suspicion=None, student_name=None, group_number=None):
        self.suspicion = suspicion
        self.student_name = student_name
        self.group_number = group_number

    def __eq__(self, other):
        return self.student_name == other.student_name


class Heap:
    def __init__(self):
        self.heap = []
        self.heap_size = 0

    def _heapify_down(self, heap, size, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2

        if left < size and heap[left].suspicion > heap[largest].suspicion:
            largest = left

        if right < size and heap[right].suspicion > heap[largest].suspicion:
            largest = right

        if largest != i:
            heap[i], heap[largest] = heap[largest], heap[i]
            self._heapify_down(heap, size, largest)

    def add_node(self, node):
        if self.heap_size == 0:
            self.heap.append(node)
        else:
            self.heap.append(node)
            for i in range((self.heap_size // 2) - 1, -1, -1):
                self._heapify_down(self.heap, self.heap_size, i)
        self.heap_size += 1

    def remove_node(self, node):
        i = 0
        for i in range(0, self.heap_size):
            if node == self.heap[i]:
                break

        self.heap[i], self.heap[self.heap_size - 1] = self.heap[self.heap_size - 1], self.heap[i]
        del self.heap[i]
        self.heap_size -= 1

        for i in range((self.heap_size // 2) - 1, -1, -1):
            self._heapify_down(self.heap, self.heap_size, i)

    def find_node(self, node):
        for record in self.heap:
            if record == node:
                return record
        return None

    def get_nodes_in_right_order(self):
        temp_heap = self.heap[:]
        temp_size = self.heap_size
        sorted_records = []

        while temp_size > 0:
            max_record = temp_heap[0]
            sorted_records.append(max_record)

            temp_heap[0] = temp_heap[temp_size - 1]
            temp_size -= 1
            temp_heap = temp_heap[:temp_size]

            self._heapify_down(temp_heap, temp_size, 0)

        return sorted_records

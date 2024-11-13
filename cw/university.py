from group import *


class Node_for_university:
    def __init__(self, suspicion, node: Students_record, heap: Group_heap):
        self.suspicion = suspicion
        self.node = node
        self.heap = heap


class University_heap:
    def __init__(self):
        self.heap = []
        self.heap_size = 0

    def heapify(self, i):
        largest = i
        l = 2 * i + 1
        r = 2 * i + 2

        if l < self.heap_size and self.heap[i].suspicion < self.heap[l].suspicion:
            largest = l

        if r < self.heap_size and self.heap[largest].suspicion < self.heap[r].suspicion:
            largest = r

        if largest != i:
            self.heap[i], self.heap[largest] = self.heap[largest], self.heap[i]
            self.heapify(largest)

    def add_record(self, record: Node_for_university):
        if self.heap_size == 0:
            self.heap.append(record)
        else:
            self.heap.append(record)
            for i in range((self.heap_size // 2) - 1, -1, -1):
                self.heapify(i)
        self.heap_size += 1

    def remove_record(self, student: Node_for_university):
        i = 0
        for i in range(0, self.heap_size):
            if student.node.name == self.heap[i].node.name:
                break

        self.heap[i], self.heap[self.heap_size - 1] = self.heap[self.heap_size - 1], self.heap[i]
        self.heap.remove(student)
        self.heap_size -= 1

        for i in range((self.heap_size // 2) - 1, -1, -1):
            self.heapify(i)

    def find_record(self, student_name):
        for record in self.heap:
            if record.node.name == student_name:
                return record
        return None

    def get_records_in_right_order(self):
        temp_heap = self.heap[:]
        temp_size = self.heap_size
        sorted_records = []

        while temp_size > 0:
            max_record = temp_heap[0]
            sorted_records.append(max_record)

            temp_heap[0] = temp_heap[temp_size - 1]
            temp_size -= 1
            temp_heap = temp_heap[:temp_size]

            self._heapify_down_temp(temp_heap, temp_size, 0)

        return sorted_records

    def _heapify_down_temp(self, heap, size, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2

        if left < size and heap[left].suspicion > heap[largest].suspicion:
            largest = left

        if right < size and heap[right].suspicion > heap[largest].suspicion:
            largest = right

        if largest != i:
            heap[i], heap[largest] = heap[largest], heap[i]
            self._heapify_down_temp(heap, size, largest)

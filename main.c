from math import ceil


class Node:
    def __init__(self, array=[]):
        self.arr = array.copy()
        self.next = None


class ListNode:
    def __init__(self, arr=[]):
        self.head = None
        self.length = 0
        self.len_of_node_array = 0
        self.make_linked_list(arr)

    def make_linked_list(self, arr):
        if len(arr) == 0:
            self.head = None
            self.length = 0
            return
        A = []
        Len = calculate_optimal_node_size(len(arr))
        self.len_of_node_array = Len
        self.length = 0
        k = 0
        lis = []
        index = 0
        while index < len(arr) or (index == len(arr) and k == Len):
            if k < Len:
                lis.append(arr[index])
                k += 1
                index += 1
            else:
                A.append(lis)
                lis = []
                k = 0

        if len(lis) != 0:
            A.append(lis)

        self.head = Node(A[0])
        self.length += 1
        for i in range(1, len(A)):
            self.add_array(Node(A[i]), self.length)

    def push_element(self, element):
        arr_elements = []
        if self.head == None:
            self.head = Node([element])
            self.length += 1
            return True
        el = self.head
        while el.next != None:
            arr_elements += el.arr
            el = el.next
        arr_elements += el.arr
        arr_elements.append(element)
        if calculate_optimal_node_size(len(arr_elements)) != self.len_of_node_array:
            self.make_linked_list(arr_elements)
            return True
        if len(el.arr) < self.len_of_node_array:
            el.arr.append(element)
            return True

        el.next = Node([element])
        self.length += 1
        return True

    def add_number(self, element, index):
        arr_elements = []
        el = self.head
        while el != None:
            arr_elements += el.arr
            el = el.next
        arr_elements.insert(index, element)

        if calculate_optimal_node_size(len(arr_elements)) != self.len_of_node_array:
            self.make_linked_list(arr_elements)
            return True

        el = self.find_node_by_index_of_element(index)

        if el == None and (index > len(arr_elements) - 1 or index < 0):
            return False
        elif el == None:
            tmp = self.head
            while tmp.next != None:
                tmp = tmp.next
            tmp.next = Node([element])
            return True
        el.arr.insert(index % self.len_of_node_array, element)
        while len(el.arr) > self.len_of_node_array:
            s = el.arr.pop(-1)
            if el.next == None:
                el.next = Node()
                self.length += 1
            el = el.next
            el.arr.insert(0, s)
        return True

    def add_array(self, element, index):
        if index == 0:
            tmp = self.head
            self.head = element
            self.head.next = tmp
            self.length += 1
            return
        el = self.head
        k = 0
        while k < index - 1 and el.next != None:
            el = el.next
            k += 1

        tmp = el.next
        el.next = Node(self.head.arr)
        el.next.arr = element.arr
        el.next.next = tmp

        self.length += 1

    def delete_number(self, index):
        arr_elements = []
        el = self.head
        while el != None:
            arr_elements += el.arr
            el = el.next

        if index >= len(arr_elements) or index < 0:
            return False

        del arr_elements[index]

        if calculate_optimal_node_size(len(arr_elements)) != self.len_of_node_array:
            self.make_linked_list(arr_elements)
            return True

        el = self.find_node_by_index_of_element(index)

        if el == None:
            return False

        del el.arr[index % self.len_of_node_array]
        if el.next == None and len(el.arr) == 0:
            self.delete_arr(index // self.len_of_node_array)
            return True
        while el.next != None:
            el.arr.append(el.next.arr[0])
            del el.next.arr[0]
            el = el.next
            if len(el.arr) == 0:
                self.delete_arr(self.length - 1)

        return True

    def find_node_by_index_of_element(self, index):
        index_arr = index // self.len_of_node_array
        el = self.head
        k = 0
        while k != index_arr and el != None:
            el = el.next
            k += 1
        return el

    def delete_arr(self, index):
        if index == 0:
            self.head = self.head.next
            self.length -= 1
            return

        el = self.head
        k = 0
        while k < index - 1 and el.next != None:
            el = el.next
            k += 1

        el.next = el.next.next
        self.length -= 1

    def find_index_of_number(self, number):
        k = 0
        index = 0
        el = self.head
        while el != None:
            if number in el.arr:
                return index + el.arr.index(number)
            index += len(el.arr)
            el = el.next
            k += 1
        return None

    def print_list(self):
        k = 0
        el = self.head
        while el != None:
            print(f"Node {k}: {' '.join([str(x) for x in el.arr])}")
            el = el.next
            k += 1


def calculate_optimal_node_size(num_elements):
    memory = num_elements * 4

    return ceil(memory / 64) + 1

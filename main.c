from math import ceil


class Node:
    def __init__(self, array=[]):
        self.arr = array.copy()
        self.next = None


class ListNode:
    def __init__(self, arr=[]):
        self.head = None
        self.length = 0
        self.len_of_node_array = 16

        self.make_linked_list(arr)

    def make_linked_list(self, arr):
        if len(arr) == 0:
            return
        self.length = 0
        k = 0
        lis = []
        index = 0
        flag_head = False
        el = self.head
        while index < len(arr):
            if k < self.len_of_node_array:
                lis.append(arr[index])
                k += 1
                index += 1
            if k >= self.len_of_node_array or index == len(arr):
                if not flag_head:
                    self.head = Node(lis)
                    self.length += 1
                    flag_head = True
                    el = self.head
                else:
                    el.next = Node(lis)
                    self.length += 1
                    el = el.next
                lis = []
                k = 0

    def push(self, element):
        if self.head == None:
            self.head = Node([element])
            return True
        el = self.head
        while el.next != None:
            el = el.next
        if len(el.arr) >= self.len_of_node_array:
            massive = el.arr
            el.arr = massive[:self.len_of_node_array // 2]
            el.next = Node(massive[self.len_of_node_array // 2:] + [element])
            self.length += 1
            return True

        el.arr.append(element)
        return True

    def insert(self, element, index):
        el, start_index, _ = self.find_node_by_index_of_element(index)
        if el is None:
            return False

        el.arr.insert(index - start_index, element)

        if len(el.arr) < self.len_of_node_array:
            return True

        half_length = self.len_of_node_array // 2
        new_array = el.arr[half_length:]
        el.arr = el.arr[:half_length]

        if el.next != None and len(el.next.arr) + len(new_array) < self.len_of_node_array:
            el.next.arr = new_array + el.next.arr
        else:
            el.next = Node(new_array)
            self.length += 1

        return True

    def delete_number(self, index):
        el, start_index, index_node = self.find_node_by_index_of_element(index)
        el_next = el.next
        #start_index_next = start_index + len(el.arr)
        index_node_next = index_node + 1
        del el.arr[index - start_index]
        if len(el.arr) == 0:
            self.head = el_next
            return
        if el_next != None:
            if len(el_next.arr) + len(el.arr) <= self.len_of_node_array:
                el.arr += el_next.arr
                self.delete_arr(index_node_next)

    def find_node_by_index_of_element(self, index):
        index_node = 0
        if index < 0:
            return None, -1, -1
        el = self.head
        k = len(el.arr)
        while k <= index:
            el = el.next
            index_node += 1
            if el == None:
                return None, -1, -1
            k += len(el.arr)
        return (el, k - len(el.arr), index_node)

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
            string = '\t'.join([str(x) for x in el.arr])
            print(f"Node {k}: {string}")
            el = el.next
            k += 1

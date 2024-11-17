from heap import *
from hash import *


class ProctoringSystem:
    def __init__(self):
        self.hash_groups = HashTable()  # хэш-таблица группа: куча группы
        self.top_records = [None] * 10

    def add_record(self, student, suspicion, group):
        record = Record(suspicion, student, group)
        self.hash_groups.insert(group, record)

        for i in range(10):
            if self.top_records[i] is None or record.suspicion > self.top_records[i].suspicion:
                self.top_records.insert(i, record)
                if len(self.top_records) > 10:
                    del self.top_records[-1]
                break

    def del_record(self, student, group):
        heap = self.hash_groups.find(group)
        record = Record(None, student, group)
        heap.remove_node(record)

        for i in range(10):
            if record == self.top_records[i]:
                del self.top_records[i]
                self.top_records.append(None)
                break

    def find_record(self, student, group):
        heap = self.hash_groups.find(group)
        record = Record(None, student, group)
        return heap.find_node(record)

    def print_records_of_group(self, group):
        for i in self.hash_groups.find(group).get_nodes_in_right_order():
            print(i.student_name)

    def add_group(self, group):
        self.hash_groups.insert(group, Heap())

    def remove_group(self, group):
        self.hash_groups.remove(group)

    def print_groups(self):
        for i in self.hash_groups.get_all_keys():
            print(i)

    def find_group(self, group):
        return self.hash_groups.find(group)

    def print_top10_records(self):
        for i in self.top_records:
            if i is None:
                break
            print(i.student_name)


sys = ProctoringSystem()
sys.add_group(3342)
sys.add_group(3343)
sys.add_group(3381)

sys.add_record("Ivanov Danila", 34, 3342)
sys.add_record("Ivanov Stepan", 11, 3342)
sys.add_record("dfgdfg", 56, 3342)
sys.add_record("hhhh", 88, 3342)
sys.add_record("Pushtk", 1, 3342)
sys.add_record("Dinar TTT", 22, 3342)

sys.del_record("Dinar TTT", 3342)

sys.print_groups()
print('-----------')
sys.print_records_of_group(3342)
print('--------')
sys.print_top10_records()
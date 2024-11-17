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
        print("Group:", group)
        for i in self.hash_groups.find(group).get_nodes_in_right_order():
            print(i.student_name, i.suspicion)

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
        print("Top 10")
        for i in self.top_records:
            if i is None:
                break
            print(i.student_name, i.group_number, i.suspicion)


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

sys.add_record("gdfsf", 57, 3343)
sys.add_record("dgfd Stdsfasepan", 48, 3343)
sys.add_record("yyui", 21, 3343)
sys.add_record("IIII", 99, 3343)

sys.add_record("suigd", 45, 3381)
sys.add_record("fhfgh fhfg", 19, 3381)
sys.add_record("fhf fhfd", 34, 3381)
sys.add_record("fh df s", 78, 3381)
sys.add_record(";'sk sudhg", 2, 3381)
sys.add_record("!!!!", 22, 3381)
sys.add_record("gdfgjo dojbg", 57, 3381)
sys.add_record("SSRTT", 43, 3381)
sys.add_record("SSRF", 81, 3381)
sys.add_record("ugff cdf", 49, 3381)


sys.print_groups()
print('-----------')
sys.print_records_of_group(3342)
print('-----------')
sys.print_records_of_group(3343)
print('-----------')
sys.print_records_of_group(3381)
print('--------')
sys.print_top10_records()

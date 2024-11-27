from hash import HashTable, Record


class ProctoringSystem:
    def __init__(self):
        self.hash_groups = HashTable()  # хэш-таблица группа: авл-дерево группы
        self.top_records = [None] * 10

    def add_record(self, student, suspicion, group):
        record = Record(suspicion, student)
        self.hash_groups.insert(group, record)
        #print(student, suspicion, self.hash_groups.find(group).find_most_suspicion(40))

        for i in range(10):
            if self.top_records[i] is None or record.suspicion > self.top_records[i].suspicion:
                self.top_records.insert(i, record)
                if len(self.top_records) > 10:
                    del self.top_records[-1]
                break

    def del_record(self, record: Record, group):
        if not record:
            print("Incorrect record!")
            return
        tree = self.hash_groups.find(group)
        tree.delete_record(record)
        #print(self.hash_groups.find(group).find_most_suspicion(40))

        for i in range(10):
            if self.top_records[i] and record == self.top_records[i]:
                del self.top_records[i]
                self.top_records.append(None)
                break

    def find_record(self, student, group):
        tree = self.hash_groups.find(group)
        if not tree:
            print("Incorrect group!")
            return
        record = Record(None, student)
        return tree.find_record(record)

    def print_records_of_group(self, group):
        print("Group:", group)
        tree = self.hash_groups.find(group)
        if not tree:
            print("Incorrect group!")
            return
        tree.print_descending()

    def add_group(self, group):
        self.hash_groups.insert(group)

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
            print(i.student_name, i.suspicion)

    def find_most_suspicion(self, n, group):
        res = self.hash_groups.find(group).find_most_suspicion(n)
        return res


sys = ProctoringSystem()
sys.add_group(3342)
sys.add_group(3442)
sys.add_group(3381)
names = ['Janet Jones', 'Constance Rodriguez', 'Margaret Hayes', 'Kyle Harris', 'Mark Mack', 'Rhonda Johnson',
         'Barbara Haynes', 'Mary Patton', 'Lauren Mason', 'Timothy Miller', 'Marc Bennett', 'Ellen Ryan',
         'John Gonzales', 'Henry Collins', 'Carol Patrick', 'Jeffrey Kelly', 'Jennifer Wilson', 'Mark Gregory',
         'Stephanie Fowler', 'Lloyd Gregory', 'Martin Shaw', 'Margaret Perry', 'Sharon Jones', 'Kenneth Garcia',
         'Jean Moore', 'Louise Johnson', 'Richard Rose', 'Michael Roberson', 'Mary White', 'Brian Houston']

susp = [53, 16, 75, 47, 37, 24, 53, 75, 79, 99, 31, 74, 25, 92, 32, 53, 1, 69, 94, 70, 80, 31, 27, 11, 75, 39, 20, 28, 58, 45]
for i in range(30):
    sys.add_record(names[i], susp[i], 3342)

node = sys.find_record('Timothy Miller', 3342)
print(node.student_name, node.suspicion)
sys.del_record(node, 3342)

sys.print_records_of_group(3342)
print(sys.find_most_suspicion(7, 3342))
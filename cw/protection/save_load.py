import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))


from src.main import ProctoringSystem, Record

def serialize(struct: ProctoringSystem):
    file = open('test.txt', 'w')
    for i in struct.hash_groups.get_all_keys():
        file.write(str(i) + '\n')
    for i in struct.hash_groups.get_all_keys():
        for j in struct.print_records_of_group(i):
            file.write(j[0] + " " + str(j[1]) + " " + str(i) + "\n")


def deserilazy(struct: ProctoringSystem):
    file = open('test.txt', 'r')
    lis = file.readlines()
    for i in lis:
        a = i.split()
        if len(a) == 1:
            struct.add_group(int(a[0]))
        else:
            struct.add_record(a[0] + a[1], int(a[2]), int(a[3]))

sys = ProctoringSystem()
'''sys.add_group(3342)
sys.add_group(1842)
sys.add_group(3781)
names = ['Janet Jones', 'Constance Rodriguez', 'Margaret Hayes', 'Kyle Harris', 'Mark Mack', 'Rhonda Johnson',
         'Barbara Haynes', 'Mary Patton', 'Lauren Mason', 'Timothy Miller', 'Marc Bennett', 'Ellen Ryan',
         'John Gonzales', 'Henry Collins', 'Carol Patrick', 'Jeffrey Kelly', 'Jennifer Wilson', 'Mark Gregory',
         'Stephanie Fowler', 'Lloyd Gregory', 'Martin Shaw', 'Margaret Perry', 'Sharon Jones', 'Kenneth Garcia',
         'Jean Moore', 'Louise Johnson', 'Richard Rose', 'Michael Roberson', 'Mary White', 'Brian Houston']

susp = [53, 16, 75, 47, 37, 24, 53, 75, 79, 99, 31, 74, 25, 92, 32, 53, 1, 69, 94, 70, 80, 31, 27, 11, 75, 39, 20,
        28, 58, 45]
for i in range(11):
    sys.add_record(names[i], susp[i], 3342)
for i in range(11, 23):
    sys.add_record(names[i], susp[i], 1842)
for i in range(23, 30):
    sys.add_record(names[i], susp[i], 3781)

sys.print_groups()

node = sys.find_record(1842, 'Ellen Ryan')
node1 = sys.find_record(3342, 'Timothy Miller')
node2 = sys.find_record(3342, None, 53)
sys.del_record(node[0], 1842)
sys.del_record(node1[0], 3342)
sys.del_record(node2[0], 3342)
sys.del_record(node2[1], 3342)
print(sys.find_most_suspicion(4, 1842))

node = sys.find_record(3342, None, 75)
sys.del_record(node[0], 3342)
sys.del_record(node[1], 3342)
sys.print_records_of_group(3342)
print(sys.find_most_suspicion(6, 3342))
print("=================")
for i in sys.print_top10_records():
    print(i)'''

deserilazy(sys)
sys.print_records_of_group(3342)
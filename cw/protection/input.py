import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))


from src.main import ProctoringSystem, Record

sys = ProctoringSystem()
print("1 - добавить запись (имя, фамилия, подозрительность, группа)\n"
        "2 - удалить запись (имя, фамилия, подозрительность, группа)\n"
        "3 - найти запись\n"
        "4 - вывести записи группы\n"
        "5 - добавить группу\n"
        "6 - удалить группу\n"
        "7 - вывести все группы\n"
        "8 - найти записи группы\n"
        "9 - вывести топ 10 записей\n"
        "10 - найти n самых подозрительных записей группы")
while True:
    a = int(input())
    if a == 1:
        name, surname, susp, group = input().split()
        sys.add_record(name + " " + surname, int(susp), int(group))
    elif a == 2:
        name, surname, susp, group = input().split()
        sys.del_record(Record(student_name=name + " " + surname, suspicion=int(susp)), int(group))
    elif a == 3:
        print("Найти по имени (1), или записи по значению подозрительности(2)?")
        b = int(input())
        if b == 1:
            name, surname, group = input().split()
            print(sys.find_record(int(group), name + " " + surname)[0])
        elif b == 2:
            susp, group = input().split()
            for i in sys.find_record(int(group), None, int(susp)):
                print(i)
    elif a == 4:
        sys.print_records_of_group(int(input()))

    elif a == 5:
        sys.add_group(int(input()))

    elif a == 6:
        sys.remove_group(int(input()))

    elif a == 7:
        sys.print_groups()

    elif a == 8:
        group = sys.find_group(int(input()))
        if group:
            print("Группа существует. Записи в ней...")
            group.print_descending()
        else:
            print("Такой группы нет")

    elif a == 9:
        for i in sys.print_top10_records():
            print(i)

    elif a == 10:
        group, n = input().split()
        for i in sys.find_most_suspicion(int(n), int(group)):
            print(i)
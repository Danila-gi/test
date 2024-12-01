from main import ProctoringSystem

"""Модуль для тестирования функций системы прокторинга"""


def make_tree_with_one_group():
    """Функция, создающее дерево для определенной группы по заданному массиву"""
    sys = ProctoringSystem()
    sys.add_group(3342)
    names = ['Janet Jones', 'Constance Rodriguez', 'Margaret Hayes', 'Kyle Harris', 'Mark Mack', 'Rhonda Johnson',
             'Barbara Haynes', 'Mary Patton']
    susp = [53, 16, 75, 47, 37, 24, 53, 75]
    for i in range(len(names)):
        sys.add_record(names[i], susp[i], 3342)
    return sys


def make_tree_with_many_groups():
    """Функция, создающее дерево для нескольких групп по заданному массиву"""
    sys = ProctoringSystem()
    sys.add_group(3342)
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
    return sys


def test_insert():
    """Тестирование вставок записей"""
    test_sys = make_tree_with_one_group().find_group(3342).root
    f1 = test_sys.left.record.student_name == "Constance Rodriguez" and test_sys.record.student_name == "Mark Mack" and \
         test_sys.right.record.student_name == "Janet Jones"
    f2 = test_sys.left.left is None and test_sys.left.right.record.student_name == "Rhonda Johnson"
    f3 = test_sys.right.left.record.student_name == "Kyle Harris" and test_sys.right.right.record.student_name == "Margaret Hayes"
    f4 = test_sys.right.left.left is None and test_sys.right.left.right.record.student_name == "Barbara Haynes"
    f5 = test_sys.right.right.left is None and test_sys.right.right.right.record.student_name == "Mary Patton"
    assert f1 and f2 and f3 and f4 and f5


def test_find_most():
    """Тестирование нахождения самых подозрительных записей группы"""
    test_sys = make_tree_with_one_group().find_group(3342)
    assert test_sys.find_most_suspicion(5) == [[75, 'Mary Patton'], [75, 'Margaret Hayes'], [53, 'Janet Jones'],
                                               [53, 'Barbara Haynes'], [47, 'Kyle Harris']]


def test_find_record_by_suspicion():
    """Тестирование нахождения записей группы по значению подозрительности"""
    test_sys = make_tree_with_one_group()
    node_1 = test_sys.find_record(3342, None, 47)
    node_2 = test_sys.find_record(3342, None, 75)
    f1 = len(node_1) == 1 and node_1[0].suspicion == 47 and node_1[0].student_name == "Kyle Harris"
    f2 = len(node_2) == 2 and node_2[0].suspicion == 75 and node_2[0].student_name == "Margaret Hayes" and \
         node_2[1].suspicion == 75 and node_2[1].student_name == "Mary Patton"
    assert f1 and f2


def test_find_record_by_name():
    """Тестирование нахождения записи группы по имени"""
    test_sys = make_tree_with_one_group()
    node = test_sys.find_record(3342, "Kyle Harris")
    node1 = test_sys.find_record(3342, "test_student")
    assert node[0].suspicion == 47 and node[0].student_name == "Kyle Harris" and node1[0] is None


def test_find_record_by_record():
    """Тестирование нахождения записи группы по всем параметрам"""
    test_sys = make_tree_with_one_group()
    node = test_sys.find_record(3342, "Kyle Harris", 47)
    node1 = test_sys.find_record(3342, "test_student", 23)
    assert node[0].suspicion == 47 and node[0].student_name == "Kyle Harris" and node1[0] is None


def test_delete_with_rotate():
    """Тестирование удаления записи с последующей балансировкой"""
    tree = make_tree_with_one_group()
    node = tree.find_record(3342, "Constance Rodriguez")[0]
    tree.del_record(node, 3342)
    test_sys = tree.find_group(3342).root
    f1 = test_sys.left.record.student_name == "Mark Mack" and test_sys.record.student_name == "Janet Jones" and \
         test_sys.right.record.student_name == "Margaret Hayes"
    f2 = test_sys.left.left.record.student_name == "Rhonda Johnson" and test_sys.left.right.record.student_name == "Kyle Harris"
    f3 = test_sys.right.left is None and test_sys.right.right.record.student_name == "Mary Patton"
    f4 = test_sys.right.right.left is None and test_sys.right.right.right is None
    f5 = test_sys.left.right.left is None and test_sys.left.right.right.record.student_name == "Barbara Haynes"
    assert f1 and f2 and f3 and f4 and f5


def test_delete_without_rotate():
    """Тестирование удаления записи без последующей балансировки"""
    tree = make_tree_with_one_group()
    node = tree.find_record(3342, "Mary Patton")[0]
    tree.del_record(node, 3342)
    test_sys = tree.find_group(3342).root
    f1 = test_sys.left.record.student_name == "Constance Rodriguez" and test_sys.record.student_name == "Mark Mack" and \
         test_sys.right.record.student_name == "Janet Jones"
    f2 = test_sys.left.left is None and test_sys.left.right.record.student_name == "Rhonda Johnson"
    f3 = test_sys.right.left.record.student_name == "Kyle Harris" and test_sys.right.right.record.student_name == "Margaret Hayes"
    f4 = test_sys.right.left.left is None and test_sys.right.left.right.record.student_name == "Barbara Haynes"
    f5 = test_sys.right.right.left is None and test_sys.right.right.right is None
    assert f1 and f2 and f3 and f4 and f5 and (tree.find_group(3342).find_most_suspicion(1) == [[75, "Margaret Hayes"]])


def test_print_records():
    """Тестирование вывода записей группы по убыванию подозрительности"""
    tree = make_tree_with_one_group()
    arr = tree.print_records_of_group(3342)
    assert arr == [['Mary Patton', 75], ['Margaret Hayes', 75], ['Janet Jones', 53], ['Barbara Haynes', 53],
                   ['Kyle Harris', 47], ['Mark Mack', 37], ['Rhonda Johnson', 24], ['Constance Rodriguez', 16]]


def test_add_groups():
    """Тестирование добавления группы в хэш-таблицу"""
    sys = make_tree_with_many_groups()
    tree_3342 = sys.find_group(3342)
    tree_1842 = sys.find_group(1842)
    tree_3781 = sys.find_group(3781)
    f1 = tree_3342 and tree_3342.print_descending() == [['Timothy Miller', 99], ['Lauren Mason', 79],
                                                        ['Mary Patton', 75],
                                                        ['Margaret Hayes', 75], ['Janet Jones', 53],
                                                        ['Barbara Haynes', 53],
                                                        ['Kyle Harris', 47], ['Mark Mack', 37], ['Marc Bennett', 31],
                                                        ['Rhonda Johnson', 24], ['Constance Rodriguez', 16]]

    f2 = tree_1842 and tree_1842.print_descending() == [['Stephanie Fowler', 94], ['Henry Collins', 92],
                                                        ['Martin Shaw', 80],
                                                        ['Ellen Ryan', 74], ['Lloyd Gregory', 70], ['Mark Gregory', 69],
                                                        ['Jeffrey Kelly', 53], ['Carol Patrick', 32],
                                                        ['Margaret Perry', 31], ['Sharon Jones', 27],
                                                        ['John Gonzales', 25], ['Jennifer Wilson', 1]]

    f3 = tree_3781 and tree_3781.print_descending() == [['Jean Moore', 75], ['Mary White', 58], ['Brian Houston', 45],
                                                        ['Louise Johnson', 39], ['Michael Roberson', 28],
                                                        ['Richard Rose', 20], ['Kenneth Garcia', 11]]
    assert f3 and f2 and f1 and sys.find_group(1111) is None


def test_top_10_records():
    """Тестирование вывода 10-ти самых подозрительных записей всех групп"""
    sys = make_tree_with_many_groups()
    assert sys.print_top10_records() == [[99, 'Timothy Miller'], [94, 'Stephanie Fowler'], [92, 'Henry Collins'],
                                         [80, 'Martin Shaw'], [79, 'Lauren Mason'], [75, 'Mary Patton'],
                                         [75, 'Margaret Hayes'], [75, 'Jean Moore'], [74, 'Ellen Ryan'],
                                         [70, 'Lloyd Gregory']]

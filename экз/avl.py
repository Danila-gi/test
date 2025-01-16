class Node:
    """Класс узла дерева с необходимыми полями"""

    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        self.height = 1


def get_height(node):
    """Функция получения высоты узла"""
    if node is None:
        return 0
    return node.height


def right_rotate(y):
    """Правый поворот дерева"""
    x = y.left
    b_node = x.right

    x.right = y
    y.left = b_node

    y.height = 1 + max(get_height(y.left), get_height(y.right))
    x.height = 1 + max(get_height(x.left), get_height(x.right))

    return x


def left_rotate(x):
    """Левый поворот дерева"""
    y = x.right
    b_node = y.left

    y.left = x
    x.right = b_node

    x.height = 1 + max(get_height(x.left), get_height(x.right))
    y.height = 1 + max(get_height(y.left), get_height(y.right))

    return y


def balance_node(node, val):
    """Функция балансировки переданного дерева"""
    balance = get_height(node.left) - get_height(node.right)
    if balance >= 2 and node.left is not None and get_height(node.left.right) <= get_height(node.left.left):
        return right_rotate(node)

    if balance <= -2 and node.right is not None and get_height(node.right.left) <= get_height(node.right.right):
        return left_rotate(node)

    if balance >= 2 and node.left is not None and get_height(node.left.right) > get_height(node.left.left):
        node.left = left_rotate(node.left)
        return right_rotate(node)

    if balance <= -2 and node.right is not None and get_height(node.right.left) > get_height(node.right.right):
        node.right = right_rotate(node.right)
        return left_rotate(node)
    return node


def insert(val, node):
    """Функция вставки в дерева новго элемента"""
    if node is None:
        return Node(val)
    if val < node.val:
        node.left = insert(val, node.left)
    else:
        node.right = insert(val, node.right)

    node.height = 1 + max(get_height(node.left), get_height(node.right))

    return balance_node(node, val)


def minimum(root):
    """Функция нахождения минимального элемента в дереве"""
    el = root
    while el.left is not None:
        el = el.left
    return el


def delete(node, val):
    """Функция удаления в дереве некоторого элемента"""
    if node is None:
        return node
    if val < node.val:
        node.left = delete(node.left, val)
    elif val > node.val:
        node.right = delete(node.right, val)
    elif node.left is not None and node.right is not None:
        node.val = minimum(node.right).val
        node.right = delete(node.right, node.val)
    elif node.left is not None:
        node = node.left
    elif node.right is not None:
        node = node.right
    else:
        node = None

    if node is None:
        return node

    node.height = 1 + max(get_height(node.left), get_height(node.right))

    return balance_node(node, val)
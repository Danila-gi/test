class Node:

    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        self.height = 1


def get_height(node):
    if node is None:
        return 0
    return node.height


def check(root):
    if root.left is None and root.right is None:
        return True
    if root.left is None and (root.right.right is not None or root.right.left is not None):
        return False
    if root.right is None and (root.left.right is not None or root.left.left is not None):
        return False
    l = root.left
    while l is not None:
        if not check(l):
            return False
        l = l.left

    r = root.right
    while r is not None:
        if not check(r):
            return False
        r = r.right
    return True


def right_rotate(y):
    x = y.left
    B = x.right

    x.right = y
    y.left = B

    y.height = 1 + max(get_height(y.left), get_height(y.right))
    x.height = 1 + max(get_height(x.left), get_height(x.right))

    return x


def left_rotate(x):
    y = x.right
    B = y.left

    y.left = x
    x.right = B

    x.height = 1 + max(get_height(x.left), get_height(x.right))
    y.height = 1 + max(get_height(y.left), get_height(y.right))

    return y


def insert(val, node):
    if node is None:
        return Node(val)
    elif val < node.val:
        node.left = insert(val, node.left)
    else:
        node.right = insert(val, node.right)

    node.height = 1 + max(get_height(node.left), get_height(node.right))

    balance = get_height(node.left) - get_height(node.right)
    if balance > 1 and val < node.left.val:
        return right_rotate(node)

    if balance < -1 and val > node.right.val:
        return left_rotate(node)

    if balance > 1 and val > node.left.val:
        node.left = left_rotate(node.left)
        return right_rotate(node)

    if balance < -1 and val < node.right.val:
        node.right = right_rotate(node.right)
        return left_rotate(node)

    return node


def minimum(root):
    el = root
    while el.left is not None:
        el = el.left
    return el


def delete(node, val):
    if node is None:
        return node
    if val < node.val:
        node.left = delete(node.left, val)
    elif val > node.val:
        node.right = delete(node.right, val)
    elif node.left is not None and node.right is not None:
        node.val = minimum(node.right).val
        node.right = delete(node.right, node.val)
    else:
        if node.left is not None:
            node = node.left
        elif node.right is not None:
            node = node.right
        else:
            node = None

    if node is None:
        return node

    node.height = 1 + max(get_height(node.left), get_height(node.right))

    balance = get_height(node.left) - get_height(node.right)
    if balance > 1 and val < node.left.val:
        return right_rotate(node)

    if balance < -1 and val > node.right.val:
        return left_rotate(node)

    if balance > 1 and val > node.left.val:
        node.left = left_rotate(node.left)
        return right_rotate(node)

    if balance < -1 and val < node.right.val:
        node.right = right_rotate(node.right)
        return left_rotate(node)

    return node


arr = [456, -125, -180, 553, 957, -181, 585, 263, -982]
root = None
for i in arr:
    root = insert(i, root)


def print_el(el):
    if el is None:
        return
    if el.left is None:
        elf = None
    else:
        elf = el.left.val
    if el.right is None:
        erf = None
    else:
        erf = el.right.val
    print(elf, el.val, erf)
    print_el(el.right)
    print_el(el.left)


print_el(root)
print('-------------')
root = delete(root, 456)
print_el(root)

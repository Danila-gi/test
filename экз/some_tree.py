class Node:
    def __init__(self, val):
        self.val = val
        self.childs = []


lis = []


def add(lis, val, parent=None):
    node = Node(val)
    lis.append(node)
    if parent:
        for i in range(len(lis)):
            if lis[i].val == parent:
                lis[i].childs.append(node)


def delete(lis, val):
    i = j = 0
    while i < len(lis):
        if lis[i].val == val:
            del lis[i]
            i += 1
            continue
        while j < len(lis[i].childs):
            if lis[i].childs[j].val == val:
                del lis[i].childs[j]
            j += 1
        i += 1
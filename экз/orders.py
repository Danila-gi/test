def in_order(root):
    if root.left is None and root.right is None:
        print(root.record.suspicion)
        return

    if root.left is not None:
        in_order(root.left)

    print(root.record.suspicion)

    if root.right is not None:
        in_order(root.right)


def pre_order(root):
    if root.left is None and root.right is None:
        print(root.record.suspicion)
        return

    print(root.record.suspicion)

    if root.left is not None:
        pre_order(root.left)

    if root.right is not None:
        pre_order(root.right)


def post_order(root):
    if root.left is None and root.right is None:
        print(root.record.suspicion)
        return

    if root.left is not None:
        post_order(root.left)

    if root.right is not None:
        post_order(root.right)

    print(root.record.suspicion)


def bfs(root):
    if root is None:
        return

    queue = []
    queue.append(root)

    while queue:
        current_node = queue.pop(0)
        print(current_node.record.suspicion)

        if current_node.left is not None:
            queue.append(current_node.left)

        if current_node.right is not None:
            queue.append(current_node.right)
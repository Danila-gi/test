class Record:
    def __init__(self, suspicion: int = None, student_name: str = None):
        self.suspicion = suspicion
        self.student_name = student_name

    def __eq__(self, other):
        if self.suspicion is None or other.suspicion is None:
            return self.student_name == other.student_name
        return self.suspicion == other.suspicion and self.student_name == other.student_name

    def __gt__(self, other):
        if self.suspicion != other.suspicion:
            return self.suspicion > other.suspicion
        return self.student_name > other.student_name

    def __lt__(self, other):
        if self.suspicion != other.suspicion:
            return self.suspicion < other.suspicion
        return self.student_name < other.student_name


class AVLNode:
    def __init__(self, record: Record):
        self.record = record
        self.left = None
        self.right = None
        self.parent = None
        self.height = 1


class AVLTree:
    def __init__(self):
        self.root = None
        self.max_node = None

    def _get_height(self, node):
        if not node:
            return 0
        return node.height

    def _get_balance(self, node):
        if not node:
            return 0
        return self._get_height(node.left) - self._get_height(node.right)

    def _update_parent(self, child, parent):
        if child:
            child.parent = parent

    def _rotate_right(self, y):
        x = y.left
        t2 = x.right

        x.right = y
        y.left = t2

        self._update_parent(x, y.parent)
        self._update_parent(y, x)
        self._update_parent(t2, y)

        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        x.height = 1 + max(self._get_height(x.left), self._get_height(x.right))

        if y == self.max_node and t2:
            self.max_node = t2
        elif y == self.max_node and not t2:
            self.max_node = x

        return x

    def _rotate_left(self, x):
        y = x.right
        t2 = y.left

        y.left = x
        x.right = t2

        self._update_parent(y, x.parent)
        self._update_parent(x, y)
        self._update_parent(t2, x)

        x.height = 1 + max(self._get_height(x.left), self._get_height(x.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))

        if x == self.max_node:
            self.max_node = y

        return y

    def insert(self, node, record: Record, parent=None):
        if not node:
            new_node = AVLNode(record)
            new_node.parent = parent

            if not self.max_node or record > self.max_node.record:
                self.max_node = new_node

            return new_node

        if record < node.record:
            node.left = self.insert(node.left, record, node)
        elif record > node.record:
            node.right = self.insert(node.right, record, node)
        else:
            return node

        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))

        balance = self._get_balance(node)

        if balance > 1 and record < node.left.record:
            return self._rotate_right(node)

        if balance < -1 and record > node.right.record:
            return self._rotate_left(node)

        if balance > 1 and record > node.left.record:
            node.left = self._rotate_left(node.left)
            return self._rotate_right(node)

        if balance < -1 and record < node.right.record:
            node.right = self._rotate_right(node.right)
            return self._rotate_left(node)

        return node

    def delete(self, node, record: Record):
        if not node:
            return node

        if record < node.record:
            node.left = self.delete(node.left, record)
        elif record > node.record:
            node.right = self.delete(node.right, record)
        else:
            if not node.left:
                if node.right:
                    node.right.parent = node.parent
                if node == self.max_node:
                    self.max_node = self._find_new_max(self.root)
                return node.right
            elif not node.right:
                if node.left:
                    node.left.parent = node.parent
                if node == self.max_node:
                    self.max_node = self._find_new_max(self.root)
                return node.left

            temp = self._get_min_value_node(node.right)
            node.record = temp.record
            node.right = self.delete(node.right, temp.record)

        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))

        balance = self._get_balance(node)

        if balance > 1 and self._get_balance(node.left) >= 0:
            return self._rotate_right(node)

        if balance > 1 and self._get_balance(node.left) < 0:
            node.left = self._rotate_left(node.left)
            return self._rotate_right(node)

        if balance < -1 and self._get_balance(node.right) <= 0:
            return self._rotate_left(node)

        if balance < -1 and self._get_balance(node.right) > 0:
            node.right = self._rotate_right(node.right)
            return self._rotate_left(node)

        return node

    def find(self, node, record: Record):
        if not node:
            return None
        if node.record == record:
            return node.record

        left_result = self.find(node.left, record)
        if left_result:
            return left_result

        return self.find(node.right, record)

    def _get_min_value_node(self, node):
        current = node
        while current.left:
            current = current.left
        return current

    def _find_new_max(self, node):
        current = node
        while current and current.right:
            current = current.right
        return current

    def insert_record(self, record: Record):
        self.root = self.insert(self.root, record)

    def delete_record(self, record: Record):
        self.root = self.delete(self.root, record)

    def find_record(self, record: Record):
        return self.find(self.root, record)

    def print_descending(self):
        self._print_descending(self.root)

    def _print_descending(self, node: AVLNode):
        if node is not None:
            self._print_descending(node.right)
            print(node.record.student_name, node.record.suspicion)
            self._print_descending(node.left)

    def find_most_suspicion(self, number_of_most: int):
        result = []
        current = self.max_node

        while current and len(result) < number_of_most:
            result.append(current.record)

            if current.left:
                current = self._find_max(current.left)
            else:
                current = current.parent

        return result

    def _find_max(self, node):
        while node and node.right:
            node = node.right
        return node
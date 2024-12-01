from graphviz import Digraph
from tree import AVLTree, AVLNode
from hash import HashTable


class AVLTreeVisualizer:
    def __init__(self, tree: AVLTree):
        self.tree = tree

    def visualize(self, group="test"):
        dot = Digraph(comment="AVL Tree")
        if self.tree.root:
            self._add_nodes(dot, self.tree.root)
        dot.render("avl_tree_for_group" + str(group), format="png", cleanup=True)
        print(f"Дерево {str(group)} сохранено")

    def _add_nodes(self, dot, node: AVLNode):
        if not node:
            return
        label = f"{node.record.suspicion}\n{node.record.student_name}"
        if node == self.tree.max_node:
            label += "\nMaxNode"
        dot.node(str(id(node)), label)

        if node.left:
            self._add_nodes(dot, node.left)
            dot.edge(str(id(node)), str(id(node.left)), label="L")
        if node.right:
            self._add_nodes(dot, node.right)
            dot.edge(str(id(node)), str(id(node.right)), label="R")


class HashTableVisualizer:
    def __init__(self, hash_table: HashTable):
        self.hash_table = hash_table

    def visualize(self, filename="hash_table"):
        dot = Digraph(comment="Hash Table")
        dot.attr(rankdir="LR")

        for i in range(self.hash_table.size):
            dot.node(f"index_{i}", f"Index {i}", shape="box")

        for i, bucket in enumerate(self.hash_table.table):
            prev_node = f"index_{i}"
            for j, (key, value) in enumerate(bucket):
                label = f"Key: {key}"
                if isinstance(value, AVLTree):
                    label += "\n(AVL Tree)"
                dot.node(f"bucket_{i}_{j}", label, shape="ellipse")
                dot.edge(prev_node, f"bucket_{i}_{j}")
                prev_node = f"bucket_{i}_{j}"

        dot.render(filename, format="png", cleanup=True)
        print(f"Хэш-таблица сохранена в файл {filename}.png")

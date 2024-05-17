from graphviz import Digraph
import math
from collections import defaultdict

class SegmentTree:
    def __init__(self, size):
        self.n = size
        self.tree = defaultdict(int)

    def update(self, idx, value, op):
        idx += self.n
        if op == '+':
            self.tree[idx] = math.gcd(self.tree[idx], value)
        elif op == '-' and self.tree[idx]:
            if self.tree[idx] == value:
                self.tree[idx] = 0

        while idx > 1:
            idx //= 2
            self.tree[idx] = math.gcd(self.tree[2 * idx], self.tree[2 * idx + 1])

    def get_gcd(self):
        return self.tree[1]

def plot_tree(tree, filename):
    dot = Digraph()
    for idx in range(1, 2 * tree.n):
        if idx in tree.tree:
            dot.node(str(idx), str(tree.tree[idx]))
            if idx // 2 in tree.tree:
                dot.edge(str(idx // 2), str(idx))
    dot.render(filename, view=False)  # Save the diagram as a file

def process_operations(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        n = int(lines[0].strip())
        segment_tree = SegmentTree(2 * n)
        for i, line in enumerate(lines[1:], start=1):
            op, num = line.strip().split()
            num = int(num)
            segment_tree.update(num - 3000000, num, op)
            if i % 20 == 0:  # Save tree diagram every 20 operations
                plot_tree(segment_tree, f"tree_at_operation_{i}")
                print(f"GCD of all numbers in the tree after {i} operations: {segment_tree.get_gcd()}")

# Update the filename path to 'operations.txt'
process_operations('tests.txt')

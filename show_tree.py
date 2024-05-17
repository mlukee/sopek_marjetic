from graphviz import Digraph
import math
from collections import defaultdict

class SegmentTree:
    def __init__(self, data):
        self.n = len(data)
        self.tree = defaultdict(int)  # Using defaultdict to handle nodes easily
        self.build(data)

    def build(self, data):
        # Insert leaf nodes in tree
        for i in range(self.n):
            self.tree[self.n + i] = data[i]
        # Build the tree by calculating GCDs
        for i in range(self.n - 1, 0, -1):
            self.tree[i] = math.gcd(self.tree[2 * i], self.tree[2 * i + 1])

    def plot_tree(self, filename):
        dot = Digraph(format='png')
        # Add non-zero nodes
        for i in range(1, 2 * self.n):
            if self.tree[i] != 0:
                dot.node(str(i), str(self.tree[i]))
                if i < self.n:  # Connect only if it is not a leaf node
                    if self.tree[2 * i] != 0:
                        dot.edge(str(i), str(2 * i))
                    if self.tree[2 * i + 1] != 0:
                        dot.edge(str(i), str(2 * i + 1))
        dot.render(filename, view=False)

def process_operations(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        numbers = []
        operation_count = 0
        for line in lines[1:]:  # Skip the first line with the count
            op, num = line.strip().split()
            num = int(num)
            if op == '+':
                numbers.append(num)
            elif op == '-' and num in numbers:
                numbers.remove(num)
            operation_count += 1
            if operation_count % 20 == 0:
                segment_tree = SegmentTree(numbers)
                segment_tree.plot_tree(f"tree_at_operation_{operation_count}")
                print(f"GCD of all numbers in the tree after {operation_count} operations: {segment_tree.tree[1]}")

# Assume the filename path to 'tests.txt' is correct
process_operations('tests.txt')

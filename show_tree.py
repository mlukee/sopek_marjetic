"""
This module contains the SegmentTree class, which provides a data structure
for efficient querying of range-based operations on an array, and a function
to process operations and plot the segment tree.
"""

import math
from collections import defaultdict
from graphviz import Digraph

class SegmentTree:
    """
    A data structure that allows efficient querying of range-based operations on an array.
    """

    def __init__(self, data):
        """
        Initialize the SegmentTree object.

        Parameters:
        - data (list): The input data for building the segment tree.
        """
        self.num_elements = len(data)  # Changed from 'n' to 'num_elements'
        self.tree = defaultdict(int)  # Using defaultdict to handle nodes easily
        self.build(data)

    def build(self, data):
        """
        Build the segment tree.

        Parameters:
        - data (list): The input data for building the segment tree.
        """
        # Insert leaf nodes in tree
        for i in range(self.num_elements):
            self.tree[self.num_elements + i] = data[i]
        # Build the tree by calculating GCDs
        for i in range(self.num_elements - 1, 0, -1):
            self.tree[i] = math.gcd(self.tree[2 * i], self.tree[2 * i + 1])

    def plot_tree(self, filename):
        """
        Plot the segment tree and save it as an image file.

        Parameters:
        - filename (str): The filename of the output image file.
        """
        dot = Digraph(format='png')
        # Add non-zero nodes
        for i in range(1, 2 * self.num_elements):
            if self.tree[i] != 0:
                dot.node(str(i), str(self.tree[i]))
                if i < self.num_elements:  # Connect only if it is not a leaf node
                    if self.tree[2 * i] != 0:
                        dot.edge(str(i), str(2 * i))
                    if self.tree[2 * i + 1] != 0:
                        dot.edge(str(i), str(2 * i + 1))
        dot.render(filename, view=False)

def process_operations():
    """
    Process the operations specified in the input file.
    """
    numbers = [12, 20, 15, 18, 23]
    numbers1 = []
    for number in numbers:
        numbers1.append(number)
        segment_tree = SegmentTree(numbers1)
        segment_tree.plot_tree(f"tree_at_operation_{number}")
        print("test123")

# Assume the filename path to 'tests.txt' is correct
process_operations()

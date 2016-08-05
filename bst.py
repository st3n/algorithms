import networkx as nx
import math
from random import shuffle
import matplotlib.pyplot as plt

class Tree:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right
        self.parent = None
        if self.left:
            self.left.parent = self
        if self.right:
            self.right.parent = self

    def __lt__(self, other):
        return self.data < other.data

    def __str__(self):
        return str(self.data)

    def to_graph(self):
       g = nx.Graph()
       for node in dfs_nodes(self):
          if node.left:
             g.add_edge(node.data, node.left.data)
          if node.right:
             g.add_edge(node.data, node.right.data)

       return g

    def get_positions(node, positions, x, y):
        if node:
            node_size = 0.5

            my_x = (x[1] + x[0]) / 2
            my_y = y[0] + (node_size / 2)

            positions[node.data] = (my_x, -my_y)
            Tree.get_positions(node.left, positions, (x[0], my_x), (my_y, y[1]))
            Tree.get_positions(node.right, positions, (my_x, x[1]), (my_y, y[1]))

    def draw(self):
        positions = {}
        Tree.get_positions(self, positions, x=(0, 10), y=(0, 10))

        print(positions)

        g = self.to_graph()

        plt.axis('on')
        nx.draw_networkx(g, positions, node_size=1500, font_size=24, node_color='g')
        plt.show()

def is_bst(tree):
    if not tree:
        return True

    left_ok = not tree.left or tree.left < tree
    right_ok = not tree.right or tree.right > tree

    return left_ok and right_ok and \
           is_bst(tree.left) and is_bst(tree.right)

def bfs_nodes(tree):
    queue = []
    queue.append(tree)

    while queue:
        node = queue.pop(0)

        if node:
            yield node
            queue.append(node.left)
            queue.append(node.right)

# deep first search
def dfs_nodes(tree):
    if tree:
        yield from dfs_nodes(tree.left)
        yield tree
        yield from dfs_nodes(tree.right)

def min_node_rec(bst):
    assert is_bst(bst) and bst is not None

    if not bst.left:
        return bst
    return min_node_rec(bst.left)

def min_node(bst):
    assert is_bst(bst) and bst is not None

    while bst.left:
        bst = bst.left

    return bst

def max_node(bst):
    assert is_bst(bst) and bst is not None

    while bst.right:
        bst = bst.right

    return bst

#next with inorder traverse
def next_node(bst):
    if bst.right:
        return min_node(bst.right)
    return bst.parent

def prev_node(bst):
    if bst.left:
        return max_node(bst.left)
    return bst.parent

begin = min_node

def end(bst):
    return None

def iterate(bst):
    it = begin(bst)
    while it != end(bst):
        yield it
        it = next_node(it)

def lower_bound(bst, x):
    assert is_bst(bst)

    if bst:
        if x < bst.data:
            res = lower_bound(bst.left, x)
            if res:
                bst = res

        elif bst.data < x:
            return lower_bound(bst.right, x)

    return bst

def insert(tree, x):
    assert is_bst(tree)

    if not tree:
        return Tree(x)

    if x < tree.data:
        if tree.left:
            return insert(tree.left, x)
        else:
            tree.left = Tree(x)
            return tree.left
    elif tree.data < x:
        if tree.right:
            return insert(tree.right, x)
        else:
            tree.right = Tree(x)
            return tree.right

    return tree

def rotate_1(tree, ):
    pass

def remove(tree, x):
    place = lower_bound(tree, x)

def create_tree_1():
    return Tree(10,
            Tree(4,
                Tree(3),
                Tree(5,
                    Tree(5))),
                Tree(20,
                    Tree(15,
                        right=Tree(17,
                            Tree(16),
                            Tree(18, right=Tree(19))))))


def create_tree_2():
   return Tree(8,
           Tree(3,
               Tree(1),
               Tree(6,
                   Tree(4),
                   Tree(7))),
               Tree(10,
                   right=Tree(14,
                       Tree(13))))

def main ():
    t = create_tree_2()
    insert(t, 5)
    insert(t, 9)
  #  print(",  ".join(map(str, dfs_nodes(t))))
  #  print(lower_bound(t, 15))
    t.draw()

if __name__ == '__main__':
    main()

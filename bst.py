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

    def __str__(self):
        return str(self.data)

    def nodes(self):
        yield from dfs_1(self)

def is_bst(tree):
    pass

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
        yield tree
        yield from dfs_nodes(tree.left)
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

    if bst.data < x:
        return lower_bound(bst.right, x)

    if x < bst.data:
        res = lower_bound(bst.left)
        if res:
            return res

def lower_bound2(bst, x):
    assert is_bst(bst)

    if not bst:
        return bst

    if x < bst.data:
        res = lower_bound2(bst.left)
    else:
        res = lower_bound2(bst.right)

    if not res: #not found
        return lower_bound2(bst.parent)
    return res

def insert(tree, x):

    place = lower_bound(tree, x)


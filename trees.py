class Tree:

    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.data)

    def nodes(self):
        yield from dfs_1(self)


def height(tree):
    if not tree:
        return 0
    return 1 + max(height(self.left), height(right.left))

def traverse_pre_order(tree, visitor):
    if tree:
        visitor(tree)
        traverse_pre_order(tree.left, visitor)
        traverse_pre_order(tree.right, visitor)

def traverse_in_order(tree, visitor):
    if tree:
        traverse_pre_order(tree.left, visitor)
        visitor(tree)
        traverse_pre_order(tree.right, visitor)

def traverse_post_order(tree, visitor):
    if tree:
        traverse_pre_order(tree.left, visitor)
        traverse_pre_order(tree.right, visitor)
        visitor(tree)

# bfs

class Queue:
    def __init__(self):
        self._data = []

    def push(self, x):
        self._data.append(x)

    def pop(self):
        return self._data.pop(0)

    def empty(self):
        return len(self._data) == 0

def bfs_tree(tree, visitor):
    queue = Queue()
    queue.push(tree)
    while not queue.empty():
        node = queue.pop()
        if node.left:
            queue.push(node.left)
        if node.right:
            queue.push(node.right)
        visitor(node)

################################for fun##############################################################
def co_numbers(max, pred):
    for i in range(max):
        if pred(i):
            yield i

def natural_numbers():
    i = 1;
    while True:
        yield i
        i += 1

#########################################################################################################
def main():

#    N = natural_numbers()
#    for i in range(10):
#        print(N.__next__())
#
#    def divided_by_3():
#        for i in co_numbers(10, lambda x: x%3 ==0):
#            yield i
#
#    def divided_by_3():
#        yield from co_numbers(10, lambda x: x%3 ==0)
#
#    for i in divided_by_3():
#        print (i)


    t = Tree("1",
            Tree("2",
                Tree("4"),
                Tree("5",
                    Tree("8"))),
            Tree("3",
                Tree("6"),
                Tree("7",
                    Tree("9",
                        Tree("10")))))

    #traverse_pre_order(t, print)

    #for node in t.nodes():
    #    print(node)

    print("BFS")
    bfs_tree(t, print)
if __name__ == '__main__':
    main()

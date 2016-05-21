""" The reason why HALF OPENED intervals it is good to use
    like STL iterators in C++:
    1. Amount of elements in intervals equal difference between
       last and first iterator)
    2. If element is not found -> iterators shows to the end()
       for anyone object.
    3. Intervals is dividable alwayse on two another hald opened intervals
    4. Such interval can contain zero elements. """

"""Python recursive binary search realization"""

def is_sorted(Arr):
    i = 0
    while (i < len(Arr) - 1):
        if (Arr[i] > Arr[i+1]):
            return False
        i += 1
    return True

def binarySearch(Arr, key):
    assert(is_sorted(Arr)), "Array is not sorted!"
    return bs(Arr, 0, len(Arr), key)

def bs(Arr, lo, hi, key):
    if (hi <= lo):
        return -1
    cmp = lo + (hi - lo) / 2
    if (Arr[cmp] > key):
        return bs(Arr, lo, cmp, key)
    elif (Arr[cmp] < key):
        return bs(Arr, cmp+1, hi, key)
    else:
        return cmp;

arr = [1, 3, 5, 5, 6, 8, 11, 12, 14, 16]
arr_bad = [1, 3, 5, 5, 6, 25, 11, 12, 14, 16]

print binarySearch(arr, 1)
#binarySearch(arr_bad, 3)




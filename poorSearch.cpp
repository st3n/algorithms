#include <cassert>

int search(int A[], int size, int key);

#define TEST_POSITIVE (int (*f)(), int A[], int size, int key) assert(search(f(A, size, key) != -1))
#define TEST_NEGATIVE (int (*f)(), int A[], int size, int key) assert(search(f(A, size, key) == -1))

int search(int A[], int size, int key)
{
	assert(size != 0);

	int i = 0;
	for (; i < size; ++i)
	{
		if (A[i] == key)
			return i;
	}
	return -1;
}

/*Test cases

1. size == 0
2. {1} {2} el: 1 degenareted trivial
3. {1,2} {3,4} el: 2
4. {2, 4, 7, 9 , 34} 
el: beg, end, mid
*/

int main ()
{
	int A1[] = {4};
	int A2[] = {1, 2};
	int A3[] = {1, 6, 3, 4};
	
	int toFind = 4; 

	TEST_POSITIVE(search, A1, 4, toFind);
	TEST_POSITIVE(search, A2, 1, toFind);
	TEST_POSITIVE(search, A3, 6, toFind);

	TEST_NEGATIVE(search, A1, 1, toFind);
	TEST_NEGATIVE(search, A2, 3, toFind);
	TEST_NEGATIVE(search, A3, 12, toFind);
	return 0;
}
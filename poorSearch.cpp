#include <cassert>
#include <iostream>

#define TEST_POSITIVE(FUNC_SEARCH, ARR, ARR_SIZE, KEY) assert(FUNC_SEARCH(ARR, ARR_SIZE, KEY) != -1)
#define TEST_NEGATIVE(FUNC_SEARCH, ARR, ARR_SIZE, KEY) assert(FUNC_SEARCH(ARR, ARR_SIZE, KEY) == -1)

int search(int A[], int size, int key)
{
	assert(size != 0);

	for (int i = 0; i < size; ++i)
	{
		if (A[i] == key)
			return i;
	}
	return -1;
}

/*********** TEST CASES ****************
* 1. {1} {2} el: 1 degenareted trivial *
* 2. {1,2} {3,4} el: 2                 *
* 3. {2, 4, 7, 9 , 34}                 *
* el: beg, end, mid                    *
***************************************/

int main ()
{
	int A1[] = {4};
	int A2[] = {1, 2};
	int A3[] = {1, 6, 3, 4};

	TEST_POSITIVE(search, A1, 1, 4);
	TEST_POSITIVE(search, A2, 2, 1);
	TEST_POSITIVE(search, A3, 4, 1);
	TEST_POSITIVE(search, A3, 4, 6);
	TEST_POSITIVE(search, A3, 4, 4);

	TEST_NEGATIVE(search, A1, 1, 1);
	TEST_NEGATIVE(search, A2, 2, 3);
	TEST_NEGATIVE(search, A3, 4, 12);

   std::cout << "All test passes!!!\n";
	return 0;
}

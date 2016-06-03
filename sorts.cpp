#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void some_sort(int a[], int len)
{
	for (int i=0; i < len; i++) {
		for (int j = i+1; j < len; j++)
		{
			if (a[i] > a[j])
			{
				swap(a, i, j);				
			}
		}
	}
}

template<class TIter>
void min_element(TIter b, TIter e)
{
	TIter result = b;
	while (b < e)
	{
		if (*b < *result)
			result = b;
		++b;
	}
	return result;
}

template<class T>
void swap(T& a, T&b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<class TIter>
void sort_naive(TIter b, TIter e)
{
	// [b, e) = [sorted) [unsorted)
	// [b, e) = [b, pivot) (pivot, e]
	for (TIter i = b; i < e; ++i)
	{
		for (TIter j = i+1; j < e; ++j)
		{
			if (*j < *i)
				swap(*i, *j);
		}
	}
}

template<class TIter>
void sort_selection(TIter b, TIter e)
{
	// [b, e) = [sorted) [unsorted)
	// [b, e) = [b, pivot) (pivot, e]
	for (TIter pivot = b; pivot < e; ++pivot)
	{
		assert(std::is_sorted(b, pivot)); // O(n)
		auto m = min_element(pivot, e);
		if (pivot != m)
			swap(*pivot, *m);
	}
}

template <class TIter>
void sort_selection_fun(TIter b, TIter e)
{
	for(TIter pivot = b; b < e; ++pivot)
		swap (*pivot, *min_element(pivot, e));
}

template <class TIter>
void sort_bubble(TIter b, TIter e)
{
	// [b, e) = [unsorted) [sorted)
	// [b, e) = [b, pivot) [pivot, e)
	for (TIter pivot = e; pivot != b; --pivot)
	{
		assert(std::is_sorted(pivot, e));
		// [b, pivot) = [b, i) [i, pivot)
		for (TIter next_i = b+1; next_i < pivot; ++next_i)
		{
			auto i = next_i-1;			
			assert (i == min_element(b, next_i));

			if (*next_i < *i)
				swap(*i, *next_i);

			assert (i == min_element(b, next_i));
		}

		assert(std::is_sorted(pivot, e));		
	}	
}

template <class TIter>
void sort_insertion(TIter b, TIter e)
{
	// [b, e) = [sorted) [unsorted)
	// [b, e) = [b, pivot) [pivot, e)
	for ()
	{
		assert(is_sorted(b, pivot));

		// insert pivot to [b, pivot)
		// [b, pivot) [*pivot] = [b, pivot) [v]
		// [b, pivot) [v] = [b, i) [v] [i, pivot]
		// [b, pivot) [v] = [b, i) [i] [i+1, pivot]
		for (TIter i = pivot; i != b; --i)
		{
			assert(is_sorted(b, i)) && assert(is_sorted(i, pivot+1));

			auto next_i = i+1;
			if (*next_i < *i)
				swap(*i, *next_i);
			else
				break;

			assert(is_sorted(b, i)) && assert(is_sorted(i, pivot+1));			
		}

		assert(is_sorted(b, pivot));
	}
}

int main(int argc, char const *argv[])
{
	
	int a[] = {8, 1, 2, 34, 13, 7, -2};
	some_sort(a, 7);
	for (int i=0; i<7; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
#include <iostream>
#include <iomanip>
#include <cassert>
#include <algorithm>

using namespace std;

bool isOk;

template <class T, class TFunc, class P1, class P2>
void test(T expected, TFunc f, P1 vec, P2 key)
{
	auto result = f(vec, key);

   if (expected != result)
	{
      cout << "Error: \n"
		     << "\texpected: " << expected
			  << " != f(" << vec << ", " << key << "), but == "
			  <<  result << endl;
      isOk = false;
		//assert(false);
	}
}

ostream& operator<<(ostream& o, const vector<int>& v)
{
	o << "{";
	for (const auto& x: v)
		o << x << ", ";
	o << "}";
	return o;
}

template <class TFunc>
void test_binary_search(TFunc binary_search_impl, string name)
{
	typedef vector<int> Vec;
	int key = 42;
   isOk = true;

	auto adaptor = [binary_search_impl](Vec& v, int key) {
		auto result = binary_search_impl(v.begin(), v.end(), key);
		return result == v.end() ? -1 : result-v.begin();
	};
	//degenarated
	test(-1, adaptor, Vec(), key);

	// triviall
	test(-1, adaptor, Vec({1}), key);
	test(0, adaptor, Vec({42}), key);


	//and 2nd trivial
	test(-1, adaptor, Vec({1, 2}), key);
	test(1, adaptor, Vec({1, 42}), key);
	test(0, adaptor, Vec({42, 100}), key);

	//key not in array
	test(-1, adaptor, Vec({1, 2, 3, 5, 41}), key);
	test(-1, adaptor, Vec({43, 45, 67, 100}), key);
	test(-1, adaptor, Vec({3, 5, 41, 43, 67}), key);

	//key in array
	test(3, adaptor, Vec({1, 2, 5, 42}), key);
	test(0, adaptor, Vec({42, 45, 67, 100}), key);
	test(2, adaptor, Vec({3, 5, 42, 45, 67}), key);

	// binary seARCH SPECIFIC
	test(3, adaptor, Vec({3, 5, 41, 42, 45, 67}), key);
	test(2, adaptor, Vec({3, 5, 42, 45, 67}), key);

	// more than one key
	test(1, adaptor, Vec({key, key}), key);
	test(3, adaptor, Vec({1, 2, key, key}), key);
	test(1, adaptor, Vec({key, key, key+1, key+10}), key);

   cout << "Tests for fucntion " << name << (isOk ? " pass" : " fail") << endl;
}

/////////////////////////////////////////////////////

template <class TIter, class T>
TIter binary_search_1(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	auto size = end-begin;

	if (size == 0)
		return end;

	if (size == 1)
		return (*begin) == key ? begin : end;

	assert(size > 1);

	auto m = begin + (end-begin)/2;

	// [begin m) [m] (m end)

	if (key < *m) // [begin, m)
	{
      auto r = binary_search_1(begin, m, key);
		return m == r ? end : r;
	}
	else  // [m, end]
		return binary_search_1(m, end, key);
}

template <class TIter, class T>
TIter binary_search_2(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	auto size = end-begin;

	if (size == 0)
		return end;

	assert(size > 0);

	auto m = begin + (end-begin)/2;

	// [begin m) [m] (m end)
	if (key < *m) // [begin, m)
	{
      auto r = binary_search_2(begin, m, key);
		return m == r ? end : r;
	}
	else if (*m < key) // [m+1, end]
		return binary_search_2(m+1, end, key);
	else // *m == key
		return m;
}

template <class TIter, class T>
TIter upper_bound_c(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	while (begin < end)
	{
		// [begin m) [m] (m end)
		auto m = begin + (end-begin)/2;

		if (*m < key) // [begin, m)
			end = m;
		else
        	begin = m+1;
     
	}
	return begin;
}

//Zu Hause:  write lower bound and test for them

template <class TIter, class T>
TIter lower_bound_c(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	while (begin < end)
	{
		// [begin m) [m] (m end)
		auto m = begin + (end-begin)/2;

		if (*m < key) // [begin, m)
			begin = m+1;
		else
			end = m;
	}
	return begin;
}

template <class TIter, class T>
TIter binary_search_lower(TIter begin, TIter end, T key)
{
	auto res = lower_bound_c(begin, end, key);
	if (res == end)
		return end;

	return *res == key ? res : end;
}

template <class TIter, class T>
TIter binary_search_upper(TIter begin, TIter end, T key)
{
	auto res = upper_bound_c(begin, end, key);
	if (res == end)
		return end;

	return *res == key ? res : end;
}

/////////////////////////////////////////////////////

void test_all_binary_searches()
{
   typedef std::vector<int> Vec;
	test_binary_search(binary_search_1<Vec::iterator, int>, "bs1");
	test_binary_search(binary_search_2<Vec::iterator, int>, "bs2");
	test_binary_search(binary_search_lower<Vec::iterator, int>, "lower bound");
	test_binary_search(binary_search_upper<Vec::iterator, int>, "upper bound");
}

int main(int argc, char const *argv[])
{
	cout << "Hello" << endl;
   test_all_binary_searches();
	return 0;
}

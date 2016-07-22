#include <iostream>
#include <iomanip>
#include <cassert>
#include <algorithm>
using namespace std;

template <class T, class TFunc, class P1, class P2>
void test(T expected, TFunc f, P1 p1, P2 p2)
{
	auto result = f(p1, p2);
    
    cout << "testing: "  << expected 
            << " == f(" << p1 << ", " << p2 << "), == "
            << result << endl;
    
    if(expected != result)
    {
        cout << "Error: \n"
            << "\texpected: "  << expected 
            << " != f(" << p1 << ", " << p2 << "), but == "
            << result << endl;
        // assert(false);
    }

}

ostream& operator<<(ostream& o, const vector<int>& v)
{
    o << "{";
    for(const auto& x : v)
        o << x << ", ";
    o << "}";
    return o;
}


template <class TFunc>
void test_binary_search(TFunc binary_search_impl)
{
	typedef vector<int> Vec;
	int key = 42;
	auto adaptor = [binary_search_impl](Vec& v, int key) { 
		auto result = binary_search_impl(v.begin(), v.end(), key);
		return result == v.end() ? -1 : result-v.begin();
	};

	// degenarated
	test(-1, adaptor, Vec(), key);
	// trivial 
    test(-1, adaptor, Vec({1}), key);
	test(-1, adaptor, Vec({100}), key);
	test(0, adaptor, Vec({42}), key);
	// and 2nd trivial
	test(-1, adaptor, Vec({1, 2}), key);
	test(1, adaptor, Vec({1, 42}), key);
	test(0, adaptor, Vec({42, 100}), key);
	// key not in array
	test(-1, adaptor, Vec({1,2,3,5,41}), key);
	test(-1, adaptor, Vec({43, 45,67,100}), key);
	test(-1, adaptor, Vec({3,5,41, 43, 45,67}), key);
	// key in array
	test(3, adaptor, Vec({1,2,5,42}), key);
	test(0, adaptor, Vec({42, 45,67,100}), key);
	test(3, adaptor, Vec({3,5,41, 42, 45,67}), key);
	// binary search specific:
	test(3, adaptor, Vec({3,5,41, 42, 45,67}), key);
	test(2, adaptor, Vec({3,5, 42, 45,67}), key);

    // more tham one key
    // test(1, adaptor, Vec({key, key}), key);
    
    // test(3, adaptor, Vec({1,2, key, key}), key);
    // test(4, adaptor, Vec({1,2,3, key, key}), key);
    
    // test(1, adaptor, Vec({key, key, key+1}), key);
    // test(1, adaptor, Vec({key, key, key+1, key+10}), key);
}

////////////////////////////////////////////////////////

template <class TIter, class T>
TIter binary_search_1(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	auto size = end-begin;
	if(size == 0)
	{
		return end;
	}
	if(size == 1)
	{
		return (*begin) == key ? begin : end;
	}
	auto m = begin + (end-begin)/2;
	if(key < *m) // [begin, m)
	{
		auto r = binary_search_1(begin, m, key);
		return m == r ? end : r;
	}
	else // [m, end)
		return binary_search_1(m, end, key);
}


template <class TIter, class T>
TIter binary_search_2(TIter begin, TIter end, T key)
{
    assert(std::is_sorted(begin, end));
    auto size = end-begin;
    if(size == 0)
    {
        return end;
    }

    assert(size > 0);
    auto m = begin + (end-begin)/2;

    // [begin m) [m] (m end)
    if(key < *m)    // [begin, m)
    {
        auto r = binary_search_2(begin, m, key);
        return m == r ? end : r;
    }
    else if(*m < key) // [m+1, end)
    {
        return binary_search_2(m+1, end, key);
    }
    else // *m == key
    {
        return m;
    }
}

template <class TIter, class T>
TIter upper_bound_1(TIter begin, TIter end, T key)
{
    assert(std::is_sorted(begin, end));
    while(begin < end)
    {
        // [begin m) [m] (m end)
        auto m = begin + (end-begin)/2;
        if(key < *m)    
        {
            end = m;        // [begin, m)
        }
        else
        {
            begin = m+1;    // [m+1, end)
        }
    }

    return begin;
}

template <class TIter, class T>
TIter binary_search_3(TIter begin, TIter end, T key)
{
    auto res = upper_bound_1(begin, end, key);
    if (res == end)
        return end;
    
    return *res == key ? res : end;
}

////////////////////////////////////////////////////////

void test_all_binary_searches()
{
    // cout << __func__ << endl;

    typedef std::vector<int> Vec;

    test_binary_search(binary_search_1<Vec::iterator, int>);
    test_binary_search(binary_search_2<Vec::iterator, int>);
	test_binary_search(binary_search_3<Vec::iterator, int>);
}

int main()
{
    cout << "Hello" << endl;

	test_all_binary_searches();

    return 0;
}

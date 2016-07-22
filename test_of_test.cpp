#include "ltest_main.hpp"

// ostream& operator<<(ostream& o, const vector<int>& v)
// {
//     o << "{";
//     for(const auto& x : v)
//         o << x << ", ";
//     o << "}";
//     return o;
// }


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


template <class TIter>
void sort_naive(TIter b, TIter e)
{
    // [b, e) = [sorted) [unsorted)
    // [b, e) = [b, pivot) [pivot, e)
    for(TIter i = b; i < e; ++i)
    {
        for(TIter j = i+1; j < e; ++j)
        {
            if(*j < *i)
                swap(*i, *j);
        }
    }
}



LTEST (search) {
    typedef vector<int> Vec;
    int key = 42;

    auto search_key = [key](const Vec& v) { 
        auto result = binary_search_1(v.begin(), v.end(), key);
        return result == v.end() ? -1 : result-v.begin();
    };

    LTEST(degenerated) {
        EXPECT_EQ(-1, search_key(Vec()));
    };
    
    LTEST(trivial) {
        EXPECT_EQ(-1, search_key({1}));
        EXPECT_EQ(-1, search_key({100}));
        EXPECT_EQ(0, search_key({42}));
    };
    
    LTEST (trivial_2nd) {
        EXPECT_EQ(-1, search_key({1, 2}));
        EXPECT_EQ(1, search_key({1, 42}));
        EXPECT_EQ(0, search_key({42, 100}));
    };

    // // key not in array
    // EXPEXCT_EQ(-1, search_key({1,2,3,5,41}));
    // EXPEXCT_EQ(-1, search_key({43, 45,67,100}));
    // EXPEXCT_EQ(-1, search_key({3,5,41, 43, 45,67}));
    // // key in array
    // EXPEXCT_EQ(3, search_key({1,2,5,42}));
    // EXPEXCT_EQ(0, search_key({42, 45,67,100}));
    // EXPEXCT_EQ(3, search_key({3,5,41, 42, 45,67}));
    // // binary search specific:
    // EXPEXCT_EQ(3, search_key({3,5,41, 42, 45,67}));
    // EXPEXCT_EQ(2, search_key({3,5, 42, 45,67}));
};


LTEST(sorting) {

    typedef std::vector<int> Vec;


    auto sort = [](Vec v){
        sort_naive(v.begin(), v.end());
        return v;
    };


    LTEST(degenerated) {
        EXPECT_EQ(Vec(), sort(Vec()));
    };

    LTEST(trivial) {
        EXPECT_EQ(Vec({1}), sort({1}));
    };

    LTEST(trivial2nd) {
        EXPECT_EQ(Vec({1, 1}), sort({1, 1}));
        EXPECT_EQ(Vec({1, 2}), sort({1, 2}));
        EXPECT_EQ(Vec({1, 2}), sort({2, 1}));
    };

    LTEST(general) {
        EXPECT_EQ(Vec({1, 2, 3, 4, 5}), sort({1, 2, 3, 4, 5}));
        EXPECT_EQ(Vec({1, 2, 3, 4, 5}), sort({5, 4, 3, 2, 1}));
        EXPECT_EQ(Vec({1, 1, 1, 1, 1}), sort({1, 1, 1, 1, 1}));
        EXPECT_EQ(Vec({1, 1, 1, 100, 100}), sort({1, 1, 1, 100, 100}));
        EXPECT_EQ(Vec({1, 1, 1, 100, 100}), sort({100, 100, 1, 1, 1}));
    };

};

////////////////////////////////////////////////////////


























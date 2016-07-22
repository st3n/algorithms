#include <iostream>

#include <iterator>

namespace limo {

template <class TIter>
struct range_type
{
    typedef TIter iterator;
    typedef const TIter const_iterator;

    typedef typename std::iterator_traits<iterator>::value_type         value_type;
    typedef typename std::iterator_traits<iterator>::reference          reference;
    typedef typename std::iterator_traits<iterator>::difference_type    difference;

    typedef difference size_type;
    
    // create:
    range_type(iterator b, iterator e): first(b), last(e) {}

    template <class TContainer>
    range_type(TContainer& c): first(c.begin()), last(c.end()) {}

    // copy move
    range_type(const range_type&) = default;
    // range_type(const range_type&&) = default;
    range_type& operator=(const range_type&) = default;
    // range_type& operator=(const range_type&&) = default;

    // emptyness:
    operator bool() const { return !empty(); }
    bool empty() const { return first == last; }

    // size:
    size_type size() const { return last-first; }

    // containel like behaviour support:
    iterator begin()   { return first; }
    iterator end()     { return last; }

    reference front()   { return *first; }
    reference back()    { return *last; }


    iterator first, last;
};


template <class TIter>
range_type<TIter> range(TIter begin, TIter end)
{
    return range_type<TIter>(begin, end);
}

template <class TContainer>
range_type<typename TContainer::iterator> range(TContainer& data)
{
    return range(data.begin(), data.end());
}

template <class TContainer>
range_type<typename TContainer::const_iterator> crange(const TContainer& data)
{
    return range(data.cbegin(), data.cend());
}

} // namespace limo



template <class TIter>
TIter min_element(limo::range_type<TIter> seqence)
{
    TIter result = seqence.begin();
    while(seqence)
    {
        if(seqence.front() < *result)
            result = seqence.first;
        seqence.first++;
    }
    return result;
}


template <class TIter>
void selection_sort(limo::range_type<TIter> unsorted)
{
    while(unsorted)
    {
        std::swap(unsorted.front(), *min_element(unsorted));
        unsorted.first++;
    }
}

// template <class TIter>
// void insertion_sort(limo::range_type<TIter> unsorted)
// {
//     TIter begin = unsorted.begin();
//     while(unsorted)
//     {
//         auto sorted = limo::range(begin, unsorted.begin());
//         while(sorted)

//     }
// }


// ostream& operator<<(ostream& o, const vector<int>& v)
// {
//     o << "{";
//     for(const auto& x : v)
//         o << x << ", ";
//     o << "}";
//     return o;
// }



#include "ltest_main.hpp"

// - context:     CONTEXT(sort, {selection_sort, naive_sort})
// - setup/teardown  anyway
// - select tests to run test_context__.run("search.*")
// - all macroses
// - statistics
// - separate printers and config

// 0.5: 
// - separate process for each test
// - perfomance testing parameters

LTEST(uplevel) {
    EXPECT_EQ(4, 2*2);
    EXPECT_EQ(4, 2*2);
    EXPECT_EQ(4, 2*2);
    EXPECT_EQ(4, 2*2);
    EXPECT_EQ(4, 2*2);
    EXPECT_EQ(4, 2*2);
};

LTEST(sorting1) {

    typedef std::vector<int> Vec;
    auto sort = [](Vec v){
        selection_sort(limo::range(v));
        return v;
    };

    int test_value = -1;

    LBEFORE {
        test_value = 42;
    };

    LAFTER {
        test_value = -1;
    };


    EXPECT_EQ(-1, test_value);
    

    // CONTEXT(sort, lmap(returner, {selection_sort, naive_sort}))


    LTEST(degenerated) {
        
        EXPECT_EQ(42, test_value);

        EXPECT_EQ(Vec(), sort(Vec()));
    };

    EXPECT_EQ(-1, test_value);

    LTEST(trivial) {

        EXPECT_EQ(42, test_value);

        EXPECT_EQ(Vec({1}), sort({1}));
    };

    EXPECT_EQ(-1, test_value);

    LTEST(trivial2nd) {
        EXPECT_EQ(Vec({1, 1}), sort({1, 1}));
        EXPECT_EQ(Vec({1, 2}), sort({1, 2}));
        EXPECT_EQ(Vec({1, 2}), sort({2, 1}));
    };

    EXPECT_EQ(-1, test_value);

    LTEST(general) {
        EXPECT_EQ(Vec({1, 2, 3, 4, 5}), sort({1, 2, 3, 4, 5}));
        EXPECT_EQ(Vec({1, 2, 3, 4, 5}), sort({5, 4, 3, 2, 1}));
        EXPECT_EQ(Vec({1, 1, 1, 1, 1}), sort({1, 1, 1, 1, 1}));
        EXPECT_EQ(Vec({1, 1, 1, 100, 100}), sort({1, 1, 1, 100, 100}));
        EXPECT_EQ(Vec({1, 1, 1, 100, 100}), sort({100, 100, 1, 1, 1}));
    };

    EXPECT_EQ(-1, test_value);


};





LTEST(sorting) {

    int test_value = -1;
    cout << "outer: " <<  (&test_value) <<endl;

    LBEFORE {
        cout << "before: " <<  (&test_value) <<endl;
        test_value = 42;
    };

    LAFTER {
        cout << "after" <<  (&test_value) << endl;
        test_value = -1;
    };


    EXPECT_EQ(-1, test_value);
    

    // CONTEXT(sort, lmap(returner, {selection_sort, naive_sort}))


    LTEST(degenerated) {
        cout << "in test: " <<  (&test_value) <<endl;
        
        EXPECT_EQ(42, test_value);

        
    };

    EXPECT_EQ(-1, test_value);

    LTEST(trivial) {

        EXPECT_EQ(42, test_value);


    };

    EXPECT_EQ(-1, test_value);

    LTEST(trivial2nd) {
        
    };

    EXPECT_EQ(-1, test_value);

    LTEST(general) {
        
    };

    EXPECT_EQ(-1, test_value);


};







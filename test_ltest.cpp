#include "ltest_main.hpp"

// + all macroses
// + __file__ ___line__
// + setup/teardown  anyway
// - print calculated values (if possible)
// - statistics
// - context:     CONTEXT(sort, {selection_sort, naive_sort})
// - select tests to run test_context__.run("search.*")
// - separate printers and config

// 0.5: 
// - separate process for each test
// - perfomance testing parameters


int foo(int x)
{
    if (x == 3)
        return 3;
    return x*x;
}


LTEST(foo) {

    using namespace ltest;

    EXPECT_TRUE(2==2);
    EXPECT_FALSE(2==3);

    EXPECT_TRUE(2==2);
    EXPECT_LT(2, 2);

    EXPECT_TRUE(in({1, 2} , 42));
    EXPECT_TRUE(in({1, 2} , 2));

    EXPECT_EQ(1, 1);

    // auto foo = [](int x) { return x * x; };
    
    LTEST(degenarated) {
        EXPECT_EQ(0, foo(0));
    };
    LTEST(trivial) {
        EXPECT_EQ(1, foo(1));
    };
        
    LTEST(even) {
        LTEST(positive) {
            EXPECT_EQ(4, foo(2));  
            EXPECT_EQ(16, foo(4));  
        };
        LTEST(negative) {
            EXPECT_EQ(4, foo(-2));  
            EXPECT_EQ(16, foo(-4));  
        };
    };


    LTEST(odd) {
        LTEST(positive) {
            EXPECT_EQ(9, foo(3));  
            EXPECT_EQ(25, foo(5));  
        };
        LTEST(negative) {
            EXPECT_EQ(9, foo(-3));  
            EXPECT_EQ(25, foo(-5));  
        };
    };
};
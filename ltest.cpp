#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <functional>
#include <string>


using namespace std;

struct Run
{
    std::string expected;
    std::string recieved;
    bool failed;
};

std::ostream& operator<<(std::ostream& o, const Run& run)
{
    return o    << run.expected << "\n    " 
                << std::setw(80) << std::setfill('.') << std::left << run.recieved
                << (run.failed ? "FAILED" : "OK");
};

class RunInfo
{
public:
    RunInfo(string test_name):m_test_name(test_name) {}

    std::string m_test_name;
    std::vector<Run> db;

    template <class T1, class T2>
    void __expect_eq(string line1, string line2, const T1& e1, const T2& e2)
    {
        Run run;
        run.expected = "expected: " + line1 + " == " + line2;
        run.recieved = "recieved: " + std::to_string(e1) + " == " + std::to_string(e2);
        run.failed = !(e1 == e2);

        std::cout << "    " << run << std::endl;

        db.push_back(run);
    }
};

class TestContext
{
public:
    typedef std::string Name;
    typedef std::function<void (TestContext&, RunInfo&)> TestFunction;
    typedef std::map<Name, TestFunction> Tests;

public:
    TestContext(Name name): m_name(name) 
    {
        if(verbose) 
            std::cout << m_name << std::endl;
    }

    void run(Name basename="")
    {
        for(const auto& test : m_tests)
        {
            TestContext context(basename + test.first);
            
            RunInfo info(context.m_name);
            test.second(context, info);
            // results[fullname] = info;

            
            context.run(context.m_name + "::");
        }
    }

    void add(Name name, TestFunction test)
    {
        m_tests[name] = test;
    }

private:
    static const bool verbose = true;
    Name  m_name;
    Tests m_tests;
    std::map<std::string, RunInfo> results;
};

TestContext ltest_context__("root");

using namespace std;

struct Wrapper
{
    typedef TestContext::TestFunction TestFunction;
    typedef std::string TestName;
    
    Wrapper(string name, TestContext* suite, TestFunction test=TestFunction())
    : m_name(name)
    , m_suite(suite) 
    , m_test(test)
    {}

    
    Wrapper operator+(TestFunction test)
    {
        return Wrapper(m_name, m_suite, test);
    }

    TestName        m_name;
    TestContext*      m_suite;
    TestFunction    m_test;
};


struct Registrator
{
    Registrator(const Wrapper& w)
    {
        w.m_suite->add(w.m_name, w.m_test);
    }
};

#define EXPECT_EQ(expr1, expr2) info__.__expect_eq(#expr1, #expr2, expr1, expr2)


#define ITEST(test_name) \
    Registrator ltest_ ## test_name = \
        Wrapper(#test_name,  &ltest_context__) + \
        [=](TestContext& ltest_context__, RunInfo& info__)


int foo(int x)
{
    if (x == 3)
        return 3;
    return x*x;
}


ITEST(foo) {

    EXPECT_EQ(1, 1);

    auto foo = [](int x) { return x * x; };
    
    ITEST(degenarated) {
        EXPECT_EQ(0, foo(0));
    };
    ITEST(trivial) {
        EXPECT_EQ(1, foo(1));
    };
        
    ITEST(even) {
        ITEST(positive) {
            EXPECT_EQ(4, foo(2));  
            EXPECT_EQ(16, foo(4));  
        };
        ITEST(negative) {
            EXPECT_EQ(4, foo(-2));  
            EXPECT_EQ(16, foo(-4));  
        };
    };


    ITEST(odd) {
        ITEST(positive) {
            EXPECT_EQ(9, foo(3));  
            EXPECT_EQ(25, foo(5));  
        };
        ITEST(negative) {
            EXPECT_EQ(9, foo(-3));  
            EXPECT_EQ(25, foo(-5));  
        };
    };



};


////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    ltest_context__.run();
    return 0;
}
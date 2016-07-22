#include <string>
#include <vector>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
// #include <utility>

#include <iostream>
#include <iomanip>

namespace ltest {

    class TestContext;
    

    typedef std::string Name;
    typedef std::function<void (TestContext&)>    TestFunction;
    typedef std::function<void(void)>             PrepareFunction;
    typedef std::map<Name, TestFunction> Tests;

    struct TestSettings
    {
        TestSettings(Name name, TestContext* suite): m_name(name), m_context(suite) {}
        
        TestSettings& operator<<(TestFunction test) {
            m_test = test;
            return *this;
        }

        Name            m_name;
        TestContext*    m_context;
        TestFunction    m_test;
    };


    struct Run
    {
        const char* expected;
        const char* recieved;
        const char* file;
        const int line;
        const bool ok;
    };

    std::ostream& operator<<(std::ostream& o, const Run& run)
    {
        const char tab[] = "    ";
        return o    << run.file << ":" << run.line << ":: " 
                    << (run.ok ? "ok" : "failed") << ": "
                    << tab << run.expected << std::endl;
                    // << tab << run.recieved << std::endl;
    };


class TestContext
{
public:
    static const bool verbose = true;
    
    PrepareFunction m_before;
    PrepareFunction m_after;

    Name  m_name;
    Tests m_tests;

    bool m_global;

public:
    TestContext(Name name, bool global=false)
    : m_name(name)
    , m_global(global)
    {
        m_before = [](){};
        m_after  = [](){};

        // if(!m_global && verbose) std::cout << m_name << std::endl;
    }

    void run(Name basename="")
    {
        for(const auto& test : m_tests)
        {
            run_test(test.first, test.second, basename);
        }
    }

    void add(Name name, TestFunction test)
    {
        m_tests[name] = test;

        if(!m_global)
        {
            run_test(name, test, m_name+".");
        }
    }


    void run_test(Name name, TestFunction test, Name basename)
    {
        m_before();
        
        TestContext context(basename + name);
        test(context);
        // results[fullname] = info;
        m_after();
        
        // context.run(context.m_name + ".");
    }

public: // outcomes
    void expect_true(const char* file, int line, const char* expected, bool ok)
    {
        Run run = {expected, ok ? "true" : "false", file, line, ok};
        // db.push_back(run);
        if(!ok) std::cout << run;
    }

private:
   
};



struct Registrator
{
    Registrator(const TestSettings& w) {
        w.m_context->add(w.m_name, w.m_test);
    }
};




#define LTEST(test_name) \
    ltest::Registrator ltest_ ## test_name = \
        ltest::TestSettings(#test_name,  &ltest_context__) << \
        [&](ltest::TestContext& ltest_context__)


#define LBEFORE ltest_context__.m_before = [&]()
#define LAFTER  ltest_context__.m_after  = [&]()


// Unary
#define EXPECT_TRUE(expr)       ltest_context__.expect_true(__FILE__, __LINE__, #expr, expr)
#define EXPECT_FALSE(expr)      EXPECT_TRUE(!(expr))

// Binary
#define EXPECT_EQ(expr1, expr2) EXPECT_TRUE((expr1) == (expr2))
#define EXPECT_NE(expr1, expr2) EXPECT_TRUE((expr1) != (expr2))
#define EXPECT_LT(expr1, expr2) EXPECT_TRUE((expr1) < (expr2))
#define EXPECT_LE(expr1, expr2) EXPECT_TRUE((expr1) <= (expr2))
#define EXPECT_GT(expr1, expr2) EXPECT_TRUE((expr1) > (expr2))
#define EXPECT_GE(expr1, expr2) EXPECT_TRUE((expr1) >= (expr2))

// Complex
template <class T1, class T2>
bool in(const std::initializer_list<T1>& s, const T2& x) {
    return std::find(s.begin(), s.end(), x) != s.end();
}
////////////////////////////////////////////////////////////////////////////////////////

} // namespace ltest

////////////////////////////////////////////////////////////////////////////////////////

ltest::TestContext ltest_context__("root", true);

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    ltest_context__.run();
    return 0;
}
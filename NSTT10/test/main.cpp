#include <gtest/gtest.h>
#include <headers/Limiter.h>


#define FABRIC_CLASSES(NAME, PARENT)                                                        \
    class NAME: PARENT {                                                                    \
        int id = -1;                                                                        \
    public:                                                                                 \
        NAME(int x = 0): id(x) {                                                            \
            std::cout << "Constructor is " << #NAME << ' ' << id << " start!" << std::endl; \
        }                                                                                   \
                                                                                            \
        ~NAME() {                                                                           \
            std::cout << "Destructor is " << #NAME << ' ' << id << " end!" << std::endl;    \
        }                                                                                   \
    };                                                                                      \

#define FABRIC_CLASSES_LIMITER(NAME, COUNT)     \
    class NAME;                                 \
    using parent_##NAME = Limiter<NAME, COUNT>; \
    FABRIC_CLASSES(NAME, parent_##NAME);        \


class LimiterTest : public ::testing::Test {
protected:
    FABRIC_CLASSES_LIMITER(Foo, 0);
    FABRIC_CLASSES_LIMITER(Bar, 4);
    FABRIC_CLASSES(Baz, Limiter<Baz>);
    FABRIC_CLASSES(Baq, Bar);
    // At the end of the file you will find information about what these macros are converted to.
};


TEST_F(LimiterTest, IsLimit_0) {
    ASSERT_THROW(Foo f, std::length_error);
    ASSERT_THROW(Foo f, std::length_error);
    ASSERT_THROW(Foo f, std::length_error);
    ASSERT_THROW(Foo f, std::length_error);
}

TEST_F(LimiterTest, IsLimit_4_First) {
    Bar br1(1), br2(2), br3(3), br4(4);
    ASSERT_THROW(Bar br5(5), std::length_error);
}


TEST_F(LimiterTest, IsLimit_4_Second) {
    {
        Bar br1(1), br2(2), br3(3), br4(4);
    }
    Bar br1(1), br2(2), br3(3), br4(4);
    ASSERT_THROW(Bar br5(5), std::length_error);
}

TEST_F(LimiterTest, IsLimit_4_Inheritance_First) {
    Bar br1(1), br2(2), br3(3), br4(4);
    ASSERT_THROW(Bar br4(5), std::length_error);
    ASSERT_THROW(Baq bq1(5), std::length_error);
}

TEST_F(LimiterTest, IsLimit_4_Inheritance_Second) {
    Bar br1(1), br2(2);
    Baq bq1(3), bq2(4);
    ASSERT_THROW(Baq bq3(5), std::length_error);
    ASSERT_THROW(Bar br3(5), std::length_error);
}

TEST_F(LimiterTest, IsLimit_4_Inheritance_Third) {
    Baq bq1(1), bq2(2);
    Bar br1(3), br2(4);
    ASSERT_THROW(Baq bq3(5), std::length_error);
    ASSERT_THROW(Bar br3(5), std::length_error);
}

TEST_F(LimiterTest, NoLimits) {
    std::vector<Baz> vb(10000);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


namespace { 
    // class Foo: Limiter<Foo, 0> {
    //     int id = -1;
    // public:
    //     Foo(int x = 0): id(x) {
    //         std::cout << "Constructor is Foo " << id << " start!" << std::endl; 
    //     }

    //     ~Foo() {
    //         std::cout << "Destructor is Foo " << id << " end!" << std::endl; 
    //     }
    // };

    // class Bar: Limiter<Bar, 4> {
    //     int id = -1;
    // public:
    //     Bar(int x = 0): id(x) {
    //         std::cout << "Constructor is Bar " << id << " start!" << std::endl; 
    //     }

    //     ~Bar() {
    //         std::cout << "Destructor is Bar " << id << " end!" << std::endl; 
    //     }
    // };

    // class Baz: Limiter<Baz> {
    //     int id = -1;
    // public:
    //     Baz(int x = 0): id(x) {
    //         std::cout << "Constructor is Baz " << id << " start!" << std::endl; 
    //     }

    //     ~Baz() {
    //         std::cout << "Destructor is Baz " << id << " end!" << std::endl; 
    //     }
    // };

    // class Baq: Bar {
    //     int id = -1;
    // public:
    //     Baq(int x = 0): id(x) {
    //         std::cout << "Constructor is Baq " << id << " start!" << std::endl; 
    //     }

    //     ~Baq() {
    //         std::cout << "Destructor is Baq " << id << " end!" << std::endl; 
    //     }
    // };
    }
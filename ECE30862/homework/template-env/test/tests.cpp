#include "gtest/gtest.h"
#include "src/lib/Base.h"

TEST(BaseShould, ReturnHello){
    Base * testBase = new Base();
    std::string actual = testBase->sayHello();
    std::string expected = "Hello!\n";
    EXPECT_EQ(expected, actual);
}

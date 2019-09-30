#include "gtest/gtest.h"
#include "src/lib/Duck.h"
#include "src/lib/Mallard.h"
#include "src/lib/RedHead.h"
#include "src/lib/DogToy.h"
#include "src/lib/Rubber.h"
#include "src/lib/Dog.h"

TEST(DogShould, ReturnBark){
    Dog * dungy = new Dog();

    std::string actual = dungy->bark();
    std::string expected = "bark!";
    EXPECT_EQ(expected, actual);
}

TEST(DogBARKShould, ReturnBarkBARK){
    Dog * dungy = new Dog();

    std::string actual = dungy->bark();
    std::string expected = "BARK!";
    EXPECT_EQ(expected, actual);
}

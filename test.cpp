#include <gtest/gtest.h>
#include "temp.cpp"

TEST(Task1, TestCase1) {
    int a = 5;
    int b = 3;
    EXPECT_EQ(add(a, b), 8);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

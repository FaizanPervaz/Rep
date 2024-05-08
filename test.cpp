#include <gtest/gtest.h>
#include "temp.cpp"

TEST(Task1, TestCase1) {
    int a = 5;
    int b = 3;
    EXPECT_EQ(add(5, 3), 8);
}

TEST(Task1, TestCase2) {
    int a = -5;
    int b = 3;
    EXPECT_EQ(add(3, -5), -2);
}

TEST(Task1, TestCase3) {
    int a = 0;
    int b = 4;
    EXPECT_EQ(add(0, 4), 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

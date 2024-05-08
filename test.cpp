#include <gtest/gtest.h>

// Test cases for add function
TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(add(3, 5), 8);
    EXPECT_EQ(add(-3, 5), 2);
}

// Test cases for subtract function
TEST(SubtractTest, PositiveNumbers) {
    EXPECT_EQ(subtract(8, 5), 3);
    EXPECT_EQ(subtract(5, 8), -3);
}

// Test cases for multiply function
TEST(MultiplyTest, PositiveNumbers) {
    EXPECT_EQ(multiply(3, 5), 15);
    EXPECT_EQ(multiply(-3, 5), -15);
}

// Test cases for divide function
TEST(DivideTest, PositiveNumbers) {
    EXPECT_FLOAT_EQ(divide(10, 5), 2.0f);
    EXPECT_FLOAT_EQ(divide(5, 2), 2.5f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

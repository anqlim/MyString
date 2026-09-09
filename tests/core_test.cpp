#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(Core, DefaultConstructor) {
    MyString str;
    ExpectCString(str, "");
    EXPECT_TRUE(str.empty());
    ExpectSizeCapacity(str, 0, 0);
}

TEST(Core, ConstructorFromCString) {
    MyString str("Hello world!");
    ExpectCString(str, "Hello world!");
    ExpectSizeCapacity(str, 12, 13);
    EXPECT_FALSE(str.empty());
}

TEST(Core, ConstructorWithCount) {
    MyString str("hello", 4);
    ExpectCString(str, "hell");
}

TEST(Core, ConstructorFill) {
    MyString str(5, '!');
    ExpectCString(str, "!!!!!");
    ExpectSizeCapacity(str, 5, 6);
}

TEST(Core, ClearKeepsCapacity) {
    MyString str("Hello world!");
    str.clear();
    ExpectCString(str, "");
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(str.capacity(), 13);
}

TEST(Core, ShrinkToFit) {
    MyString str("Hello world!");
    str.erase(5, 6);
    ExpectCString(str, "Hello!");
    str.shrink_to_fit();
    ExpectSizeCapacity(str, 6, 7);
}

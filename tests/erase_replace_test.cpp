#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(EraseReplace, Erase) {
    MyString str("Hello world!");
    str.erase(5, 6);
    ExpectCString(str, "Hello!");
}

TEST(EraseReplace, Replace) {
    MyString str("Hello!");
    str.replace(0, 5, "Hi");
    ExpectCString(str, "Hi!");

    str = "abcdef";
    str.replace(2, 2, "ZZZ");
    ExpectCString(str, "abZZZef");
}

TEST(EraseReplace, ReplaceOnEmptyStringWithNullData) {
    MyString str;
    str.replace(0, 0, "");
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(str.c_str()[0], '\0');

    str.clear();
    str.shrink_to_fit();
    str.replace(0, 0, "");
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(str.capacity(), 0U);
}

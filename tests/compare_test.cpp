#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(Compare, CompareAndRelations) {
    MyString a("abc");
    MyString b("abd");
    MyString c("abc");

    EXPECT_LT(a.compare(b), 0);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
}

TEST(Compare, Concatenation) {
    MyString a("abc");
    MyString sum = a + "!";
    ExpectCString(sum, "abc!");

    a += "!";
    ExpectCString(a, "abc!");
}

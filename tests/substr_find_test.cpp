#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(SubstrFind, Substr) {
    MyString str("Hello world!");
    MyString sub = str.substr(6, 5);
    ExpectCString(sub, "world");
}

TEST(SubstrFind, Find) {
    MyString str("Hello world!");
    EXPECT_EQ(str.find("world"), 6);
    EXPECT_EQ(str.find("o", 5), 7);
    EXPECT_EQ(str.find("xyz"), -1);

    MyString pattern("wor");
    EXPECT_EQ(str.find(pattern), 6);
}

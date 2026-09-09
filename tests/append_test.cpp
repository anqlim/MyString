#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(Append, CString) {
    MyString str("ab");
    str.append("cd");
    ExpectCString(str, "abcd");
}

TEST(Append, CountAndChar) {
    MyString str("ab");
    str.append(2, '!');
    ExpectCString(str, "ab!!");
}

TEST(Append, MyString) {
    MyString str("ab");
    MyString tail("XY");
    str.append(tail);
    ExpectCString(str, "abXY");
}

TEST(Append, CStringWithCount) {
    MyString str("ab");
    str.append("hello", 2);
    ExpectCString(str, "abhe");
}

TEST(Append, CStringWithIndexAndCount) {
    MyString str("ab");
    str.append("world", 1, 3);
    ExpectCString(str, "aborl");
}

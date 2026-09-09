#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(Assignment, FromCString) {
    MyString str;
    str = "hello";
    ExpectCString(str, "hello");
}

TEST(Assignment, FromChar) {
    MyString str;
    str = '!';
    ExpectCString(str, "!");
}

TEST(Assignment, CopyFromMyString) {
    MyString source("copy");
    MyString str;
    str = source;
    ExpectCString(str, "copy");
}

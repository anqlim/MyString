#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(Insert, CountAndChar) {
    MyString str("aaaaa");
    str.insert(0, 1, '!');
    ExpectCString(str, "!aaaaa");

    str.insert(3, 2, '@');
    ExpectCString(str, "!aa@@aaa");
}

TEST(Insert, CStringWithCount) {
    MyString str("aaaaa");
    str.insert(1, "@@@@@", 2);
    ExpectCString(str, "a@@aaaa");
}

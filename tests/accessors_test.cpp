#include "test_helpers.h"

#include <gtest/gtest.h>

TEST(Accessors, OperatorIndex) {
    MyString str("hello");
    str[0] = 'H';
    EXPECT_EQ(str[0], 'H');
    ExpectCString(str, "Hello");
}

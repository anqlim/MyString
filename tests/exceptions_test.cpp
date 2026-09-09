#include "test_helpers.h"

#include <gtest/gtest.h>

#include <stdexcept>

TEST(Exceptions, SubstrOutOfRange) {
    MyString str("abc");
    EXPECT_THROW(str.substr(10, 1), std::out_of_range);
}

TEST(Exceptions, EraseOutOfRange) {
    MyString str("abc");
    EXPECT_THROW(str.erase(0, 10), std::out_of_range);
}

#ifndef MYSTRING_TEST_HELPERS_H
#define MYSTRING_TEST_HELPERS_H

#include "mystring.h"

#include <gtest/gtest.h>

#include <string>

inline void ExpectCString(const MyString& actual, const char* expected) {
    EXPECT_STREQ(actual.c_str(), expected);
}

inline void ExpectSizeCapacity(const MyString& str, std::size_t size, std::size_t capacity) {
    EXPECT_EQ(str.size(), size);
    EXPECT_EQ(str.capacity(), capacity);
}

#endif

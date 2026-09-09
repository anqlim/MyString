#include <gtest/gtest.h>

#include "mystring.h"

TEST(Iterators62Test, BeginEndTraversal) {
    MyString str("abc");
    std::string result;

    for (auto it = str.begin(); it != str.end(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "abc");
}

TEST(Iterators62Test, ConstIteratorTraversal) {
    const MyString str("xyz");
    std::string result;

    for (auto it = str.cbegin(); it != str.cend(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "xyz");
}

TEST(Iterators62Test, ReverseIteratorTraversal) {
    MyString str("abc");
    std::string result;

    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "cba");
}

TEST(Iterators62Test, ConstReverseIteratorTraversal) {
    const MyString str("abc");
    std::string result;

    for (auto it = str.rcbegin(); it != str.rcend(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "cba");
}

TEST(Iterators62Test, InsertByIterator) {
    MyString str("hello");
    auto it = str.begin();
    ++it;
    ++it;
    str.insert(it, "XX");

    EXPECT_EQ(str, "heXXllo");
}

TEST(Iterators62Test, EraseByIteratorRange) {
    MyString str("hello");
    auto first = str.begin();
    ++first;
    auto last = first;
    ++last;
    ++last;
    ++last;
    str.erase(first, last);

    EXPECT_EQ(str, "ho");
}

TEST(Iterators62Test, SubstrByIterator) {
    const MyString str("hello");
    auto first = str.cbegin();
    ++first;
    auto last = first;
    ++last;
    ++last;
    ++last;

    EXPECT_EQ(str.substr(first, last), "ell");
}

TEST(Iterators62Test, FindByIterator) {
    const MyString str("abracadabra");
    auto start = str.cbegin();
    ++start;

    EXPECT_EQ(str.find("ca", start), 4);
}

TEST(Iterators62Test, AccessByIterator) {
    MyString str("abc");
    auto it = str.begin();
    ++it;

    str.at(it) = 'Z';
    EXPECT_EQ(str[1], 'Z');
    EXPECT_EQ(str.at(it), 'Z');
}

TEST(Iterators62Test, IteratorArithmetic) {
    MyString str("abcde");
    EXPECT_EQ(*(str.begin() + 2), 'c');
    EXPECT_EQ(*(2 + str.begin()), 'c');
    EXPECT_EQ(str.end() - str.begin(), 5);

    auto it = str.begin() + 1;
    it += 2;
    EXPECT_EQ(*it, 'd');
    it -= 1;
    EXPECT_EQ(*it, 'c');

    EXPECT_EQ(*(str.rbegin() + 1), 'd');
    EXPECT_EQ(str.rend() - str.rbegin(), 5);
}

TEST(Iterators62Test, EmptyStringIterators) {
    MyString str;
    EXPECT_EQ(str.begin(), str.end());
    EXPECT_EQ(str.rbegin(), str.rend());
    EXPECT_EQ(str.cbegin(), str.cend());
    EXPECT_EQ(str.rcbegin(), str.rcend());
}

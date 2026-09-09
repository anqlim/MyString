#include "test_helpers.h"

#include <fstream>
#include <limits>
#include <string>
#include <utility>

#include <gtest/gtest.h>

TEST(Move, MoveConstructorStealsBuffer) {
    MyString source("hello");
    const std::size_t capacity = source.capacity();

    MyString moved(std::move(source));
    ExpectCString(moved, "hello");
    EXPECT_EQ(moved.capacity(), capacity);

    EXPECT_TRUE(source.empty());
    EXPECT_EQ(source.size(), 0);
    EXPECT_EQ(source.capacity(), 0);
}

TEST(Move, MoveAssignmentStealsBuffer) {
    MyString source("move me");
    MyString target("old");

    target = std::move(source);
    ExpectCString(target, "move me");
    EXPECT_TRUE(source.empty());
}

TEST(ConversionCtor, IntAndDouble) {
    MyString from_int(42);
    ExpectCString(from_int, "42");

    MyString from_negative(-7);
    ExpectCString(from_negative, "-7");

    MyString from_double(0.05);
    ExpectCString(from_double, "0.05");
}

TEST(ConversionCtor, DoubleRejectsNonFinite) {
    const double nan_value = std::numeric_limits<double>::quiet_NaN();
    const double inf_value = std::numeric_limits<double>::infinity();
    EXPECT_THROW(static_cast<void>(MyString(nan_value)), MyStringConversionError);
    EXPECT_THROW(static_cast<void>(MyString(inf_value)), MyStringConversionError);
}

TEST(At, ReturnsCharacter) {
    const MyString str("abc");
    EXPECT_EQ(str.at(1), 'b');
    EXPECT_EQ(const_cast<MyString&>(str).at(2), 'c');
}

TEST(At, ThrowsOnInvalidIndex) {
    MyString str("abc");
    EXPECT_THROW(str.at(3), std::out_of_range);
    EXPECT_THROW(str.at(-1), std::out_of_range);
}

TEST(ToInt, ParsesInteger) {
    EXPECT_EQ(MyString("0").to_int(), 0);
    EXPECT_EQ(MyString("42").to_int(), 42);
    EXPECT_EQ(MyString("-15").to_int(), -15);
    EXPECT_EQ(MyString("+9").to_int(), 9);
}

TEST(ToInt, RejectsInvalidInput) {
    EXPECT_THROW(MyString("").to_int(), MyStringConversionError);
    EXPECT_THROW(MyString("12a").to_int(), MyStringConversionError);
    EXPECT_THROW(MyString("-").to_int(), MyStringConversionError);
}

TEST(ToFloat, ParsesDouble) {
    EXPECT_DOUBLE_EQ(MyString("3.14").to_float(), 3.14);
    EXPECT_DOUBLE_EQ(MyString("-2.5").to_float(), -2.5);
}

TEST(ToFloat, RejectsInvalidInput) {
    EXPECT_THROW(MyString("").to_float(), MyStringConversionError);
    EXPECT_THROW(MyString("1.2.3").to_float(), MyStringConversionError);
}

TEST(FileIo, WriteAndRead) {
    const char* path = "mystring_file_io_tmp.txt";
    MyString written("hello file");

    std::ofstream out(path);
    out << written;
    out.close();

    MyString read;
    std::ifstream in(path);
    in >> read;
    in.close();

    ExpectCString(read, "hello");
    std::remove(path);
}

TEST(FindAny, FirstLeftmostMatch) {
    MyString text("hello amazing world");
    auto result = text.find_any({"world", "amazing"});
    EXPECT_EQ(result.first, 6);
    EXPECT_EQ(result.second, 1);
}

TEST(FindAny, RespectsStart) {
    MyString text("hello amazing world amazing");
    auto result = text.find_any({"amazing"}, 7);
    EXPECT_EQ(result.first, 20);
    EXPECT_EQ(result.second, 0);
}

TEST(FindAny, ShorterPatternWinsWhenItMatchesEarlier) {
    MyString text("ababa");
    auto result = text.find_any({"a", "aba"});
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

TEST(FindAny, FindsSuffixPattern) {
    MyString text("xxaba");
    auto result = text.find_any({"aba", "ba"});
    EXPECT_EQ(result.first, 2);
    EXPECT_EQ(result.second, 0);
}

TEST(FindAny, OverlappingPattern) {
    MyString text("aaaa");
    auto result = text.find_any({"aa"});
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

TEST(FindAny, NotFound) {
    MyString text("hello");
    auto result = text.find_any({"xyz", "zzz"});
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

TEST(FindAny, EmptyPatternList) {
    MyString text("hello");
    auto result = text.find_any(std::initializer_list<const char*>{});
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

TEST(FindAny, MatchesFindForSinglePattern) {
    MyString text("hello world");
    EXPECT_EQ(text.find("world"), text.find_any({"world"}).first);
}

TEST(FindAny, StringOverload) {
    MyString text("hello world");
    auto result = text.find_any({std::string("world"), std::string("hello")});
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 1);
}

TEST(FindAny, MyStringOverload) {
    MyString text("hello world");
    MyString pattern("world");
    auto result = text.find_any({pattern});
    EXPECT_EQ(result.first, 6);
    EXPECT_EQ(result.second, 0);
}

TEST(FindAny, StartOutOfRange) {
    MyString text("abc");
    EXPECT_THROW(text.find_any({"a"}, 5), std::out_of_range);
}

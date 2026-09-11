#include "mystring.h"

#include <cmath>
#include <cstdint>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

namespace {

constexpr std::size_t kMaxCommands = 512;
constexpr std::size_t kMaxChunk = 256;
constexpr std::size_t kMaxStringSize = 4096;

struct Reader {
    const std::uint8_t* data = nullptr;
    std::size_t size = 0;
    std::size_t pos = 0;

    bool read_u8(std::uint8_t& out) {
        if (pos >= size) {
            return false;
        }
        out = data[pos++];
        return true;
    }

    bool read_u16(std::uint16_t& out) {
        std::uint8_t hi = 0;
        std::uint8_t lo = 0;
        if (!read_u8(hi) || !read_u8(lo)) {
            return false;
        }
        out = static_cast<std::uint16_t>((static_cast<std::uint16_t>(hi) << 8) | lo);
        return true;
    }

    bool read_bytes(std::size_t count, std::vector<char>& out) {
        if (count > kMaxChunk || pos + count > size) {
            return false;
        }
        out.assign(reinterpret_cast<const char*>(data + pos),
                   reinterpret_cast<const char*>(data + pos + count));
        pos += count;
        return true;
    }

    bool read_cstr(std::string& out) {
        std::uint8_t len = 0;
        if (!read_u8(len)) {
            return false;
        }
        std::vector<char> bytes;
        if (!read_bytes(len, bytes)) {
            return false;
        }
        out.assign(bytes.begin(), bytes.end());
        return true;
    }
};

std::vector<std::uint8_t> read_input_file(const char* path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return {};
    }
    return std::vector<std::uint8_t>(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

MyString make_from_cstr(const std::string& s) {
    if (s.empty()) {
        return MyString();
    }
    return MyString(s.c_str());
}

int bounded_index(std::uint16_t raw, int limit) {
    if (limit <= 0) {
        return 0;
    }
    return static_cast<int>(raw % static_cast<std::uint16_t>(limit + 1));
}

void exercise_constructors(MyString& s, Reader& r) {
    std::string tmp;
    std::uint8_t b0 = 0;
    std::uint8_t b1 = 0;

    s = MyString();

    if (r.read_cstr(tmp) && !tmp.empty()) {
        s = MyString(tmp.c_str());
        s = MyString(tmp);
        if (r.read_u8(b0) && b0 > 0) {
            const int count = static_cast<int>(b0 % 32);
            try {
                s = MyString(tmp.c_str(), count);
                s = MyString(tmp, count);
            } catch (...) {
            }
        }
    }

    if (r.read_u8(b0) && r.read_u8(b1)) {
        s = MyString(static_cast<int>(b0 % 32), static_cast<char>(b1));
    }

    if (r.read_u8(b0)) {
        try {
            s = MyString(static_cast<int>(b0));
        } catch (...) {
        }
        try {
            s = MyString(static_cast<double>(b0) / 10.0);
        } catch (...) {
        }
    }

    MyString other = s;
    s = MyString(other);
    if (r.read_u8(b0) && b0 > 0) {
        try {
            s = MyString(other, static_cast<int>(b0 % 32));
        } catch (...) {
        }
    }

    MyString moved = s;
    s = MyString(std::move(moved));
}

void exercise_assignment(MyString& s, Reader& r) {
    std::string tmp;
    std::uint8_t b0 = 0;

    if (r.read_cstr(tmp)) {
        s = tmp.c_str();
        s = tmp;
    }

    MyString other = s;
    s = other;

    if (r.read_u8(b0)) {
        s = static_cast<char>(b0);
    }

    MyString donor = s;
    s = std::move(donor);
}

void exercise_core(MyString& s, Reader& r) {
    std::uint8_t b0 = 0;
    s.clear();
    if (r.read_u8(b0) && (b0 % 2) == 1) {
        s.shrink_to_fit();
    }
    (void)s.c_str();
    (void)s.size();
    (void)s.capacity();
    (void)s.empty();
}

void exercise_append(MyString& s, Reader& r) {
    std::string tmp;
    std::uint8_t b0 = 0;
    std::uint8_t b1 = 0;
    std::uint8_t b2 = 0;

    if (r.read_u8(b0) && r.read_u8(b1)) {
        s.append(static_cast<int>(b0 % 16), static_cast<char>(b1));
    }

    if (!r.read_cstr(tmp) || tmp.empty()) {
        return;
    }

    MyString ms = make_from_cstr(tmp);
    s.append(tmp.c_str());
    s.append(tmp);
    s.append(ms);

    if (r.read_u8(b0) && b0 > 0) {
        const int count = static_cast<int>(b0 % static_cast<std::uint8_t>(tmp.size() + 1));
        s.append(tmp.c_str(), count);
        s.append(tmp, count);
        s.append(ms, count);
    }

    if (r.read_u8(b0) && r.read_u8(b1) && r.read_u8(b2) && b1 < tmp.size()) {
        const int s_index = static_cast<int>(b0 % tmp.size());
        const int count = static_cast<int>(b2 % (tmp.size() - s_index + 1));
        s.append(tmp.c_str(), s_index, count);
        s.append(tmp, s_index, count);
        s.append(ms, s_index, count);
    }
}

void exercise_insert_index(MyString& s, Reader& r) {
    std::string tmp;
    std::uint16_t u16 = 0;
    std::uint8_t b0 = 0;
    std::uint8_t b1 = 0;
    std::uint8_t b2 = 0;

    if (r.read_u16(u16) && r.read_u8(b0) && r.read_u8(b1)) {
        const int index = bounded_index(u16, static_cast<int>(s.size()));
        s.insert(index, static_cast<int>(b0 % 16), static_cast<char>(b1));
    }

    if (!r.read_u16(u16) || !r.read_cstr(tmp)) {
        return;
    }

    const int index = bounded_index(u16, static_cast<int>(s.size()));
    MyString ms = make_from_cstr(tmp);
    s.insert(index, tmp.c_str());
    s.insert(index, tmp);
    s.insert(index, ms);

    if (r.read_u8(b0) && b0 > 0) {
        const int count = static_cast<int>(b0 % static_cast<std::uint8_t>(tmp.size() + 1));
        s.insert(index, tmp.c_str(), count);
        s.insert(index, tmp, count);
        s.insert(index, ms, count);
    }

    if (r.read_u8(b0) && r.read_u8(b1) && r.read_u8(b2) && !tmp.empty() && b1 < tmp.size()) {
        const int s_index = static_cast<int>(b0 % tmp.size());
        const int count = static_cast<int>(b2 % (tmp.size() - s_index + 1));
        s.insert(index, tmp.c_str(), s_index, count);
        s.insert(index, tmp, s_index, count);
        s.insert(index, ms, s_index, count);
    }
}

void exercise_insert_iterator(MyString& s, Reader& r) {
    if (s.empty()) {
        return;
    }

    std::string tmp;
    std::uint8_t b0 = 0;
    std::uint8_t b1 = 0;
    std::uint8_t b2 = 0;

    auto pos = s.begin();
    if (r.read_u8(b0) && (b0 % 2) == 1 && s.size() > 1) {
        ++pos;
    }

    if (r.read_u8(b0) && r.read_u8(b1)) {
        s.insert(pos, static_cast<int>(b0 % 8), static_cast<char>(b1));
    }

    if (!r.read_cstr(tmp)) {
        return;
    }

    MyString ms = make_from_cstr(tmp);
    s.insert(pos, tmp.c_str());
    s.insert(pos, tmp);
    s.insert(pos, ms);

    if (r.read_u8(b0) && b0 > 0) {
        const int count = static_cast<int>(b0 % static_cast<std::uint8_t>(tmp.size() + 1));
        s.insert(pos, tmp.c_str(), count);
        s.insert(pos, tmp, count);
        s.insert(pos, ms, count);
    }

    if (r.read_u8(b0) && r.read_u8(b1) && r.read_u8(b2) && !tmp.empty() && b1 < tmp.size()) {
        const int s_index = static_cast<int>(b0 % tmp.size());
        const int count = static_cast<int>(b2 % (tmp.size() - s_index + 1));
        s.insert(pos, tmp.c_str(), s_index, count);
        s.insert(pos, tmp, s_index, count);
        s.insert(pos, ms, s_index, count);
    }
}

void exercise_erase(MyString& s, Reader& r) {
    std::uint16_t u16 = 0;
    std::uint8_t b0 = 0;

    if (r.read_u16(u16) && r.read_u8(b0) && !s.empty()) {
        const int index = bounded_index(u16, static_cast<int>(s.size() - 1));
        s.erase(index, static_cast<int>(b0 % 32));
    }

    if (s.empty() || !r.read_u8(b0)) {
        return;
    }

    auto pos = s.begin();
    if ((b0 % 2) == 1 && s.size() > 1) {
        ++pos;
    }
    s.erase(pos);

    if (s.size() > 1) {
        auto first = s.begin();
        auto last = s.end();
        s.erase(first, last);
    }
}

void exercise_replace_index(MyString& s, Reader& r) {
    std::string tmp;
    std::uint16_t u16 = 0;
    std::uint8_t b0 = 0;
    std::uint8_t b1 = 0;
    std::uint8_t b2 = 0;

    if (!r.read_u16(u16) || !r.read_u8(b0) || !r.read_cstr(tmp)) {
        return;
    }

    const int index = bounded_index(u16, static_cast<int>(s.size()));
    const int count = static_cast<int>(b0 % 32);
    MyString ms = make_from_cstr(tmp);

    s.replace(index, count, tmp.c_str());
    s.replace(index, count, tmp);
    s.replace(index, count, ms);

    if (r.read_u8(b1) && b1 > 0) {
        const int s_count = static_cast<int>(b1 % static_cast<std::uint8_t>(tmp.size() + 1));
        s.replace(index, count, tmp.c_str(), s_count);
        s.replace(index, count, tmp, s_count);
        s.replace(index, count, ms, s_count);
    }

    if (r.read_u8(b1) && r.read_u8(b2) && !tmp.empty() && b1 < tmp.size()) {
        const int s_index = static_cast<int>(b1 % tmp.size());
        const int s_count = static_cast<int>(b2 % (tmp.size() - s_index + 1));
        s.replace(index, count, tmp.c_str(), s_index, s_count);
        s.replace(index, count, tmp, s_index, s_count);
        s.replace(index, count, ms, s_index, s_count);
    }
}

void exercise_replace_iterator(MyString& s, Reader& r) {
    if (s.empty()) {
        return;
    }

    std::string tmp;
    std::uint8_t b0 = 0;
    std::uint8_t b1 = 0;
    std::uint8_t b2 = 0;

    auto pos = s.begin();
    if (r.read_u8(b0) && (b0 % 2) == 1 && s.size() > 1) {
        ++pos;
    }

    if (!r.read_u8(b0) || !r.read_cstr(tmp)) {
        return;
    }

    const int count = static_cast<int>(b0 % 8);
    MyString ms = make_from_cstr(tmp);

    s.replace(pos, count, tmp.c_str());
    s.replace(pos, count, tmp);
    s.replace(pos, count, ms);

    if (r.read_u8(b1) && b1 > 0) {
        const int s_count = static_cast<int>(b1 % static_cast<std::uint8_t>(tmp.size() + 1));
        s.replace(pos, count, tmp.c_str(), s_count);
        s.replace(pos, count, tmp, s_count);
        s.replace(pos, count, ms, s_count);
    }

    if (r.read_u8(b1) && r.read_u8(b2) && !tmp.empty() && b1 < tmp.size()) {
        const int s_index = static_cast<int>(b1 % tmp.size());
        const int s_count = static_cast<int>(b2 % (tmp.size() - s_index + 1));
        s.replace(pos, count, tmp.c_str(), s_index, s_count);
        s.replace(pos, count, tmp, s_index, s_count);
        s.replace(pos, count, ms, s_index, s_count);
    }
}

void exercise_substr_find(MyString& s, Reader& r) {
    std::string tmp;
    std::uint16_t u16 = 0;
    std::uint8_t b0 = 0;

    if (r.read_u16(u16) && r.read_u8(b0)) {
        const int index = bounded_index(u16, static_cast<int>(s.size()));
        (void)s.substr(index);
        (void)s.substr(index, static_cast<int>(b0 % 32));
    }

    if (!s.empty()) {
        auto cit = s.cbegin();
        if (s.size() > 1) {
            ++cit;
        }
        (void)s.substr(cit);
        (void)s.substr(cit, 1);
        auto first = s.cbegin();
        auto last = s.cend();
        if (first != last) {
            (void)s.substr(first, last);
        }
    }

    if (!r.read_cstr(tmp)) {
        return;
    }

    MyString pattern = make_from_cstr(tmp);
    (void)s.find(tmp.c_str());
    (void)s.find(tmp);
    (void)s.find(pattern);
    (void)s.find(tmp.c_str(), 0);
    (void)s.find(tmp, 0);
    (void)s.find(pattern, 0);

    if (!s.empty()) {
        (void)s.find(tmp.c_str(), s.cbegin());
        (void)s.find(tmp, s.cbegin());
        (void)s.find(pattern, s.cbegin());
    }
}

void exercise_compare_operators(MyString& s, Reader& r) {
    std::string tmp;
    if (!r.read_cstr(tmp)) {
        return;
    }

    MyString other = make_from_cstr(tmp);
    (void)s.compare(other);
    (void)(s == other);
    (void)(s != other);
    (void)(s < other);
    (void)(s > other);
    (void)(s <= other);
    (void)(s >= other);

    s += tmp.c_str();
    s += tmp;
    s += other;
    (void)(s + tmp.c_str());
    (void)(s + tmp);
    (void)(s + other);
}

void exercise_accessors(MyString& s, Reader& r) {
    std::uint16_t u16 = 0;
    std::uint8_t b0 = 0;

    if (s.empty() || !r.read_u16(u16)) {
        return;
    }

    const int index = bounded_index(u16, static_cast<int>(s.size() - 1));
    try {
        (void)s[index];
        (void)s.at(index);
        if (r.read_u8(b0) && (b0 % 2) == 1) {
            s[index] = static_cast<char>('a' + (b0 % 26));
            s.at(index) = static_cast<char>('z' - (b0 % 26));
        }
    } catch (...) {
    }

    if (s.empty()) {
        return;
    }

    auto it = s.begin();
    auto cit = s.cbegin();
    try {
        (void)s[it];
        (void)s[cit];
        (void)s.at(it);
        (void)s.at(cit);
    } catch (...) {
    }
}

void exercise_iterators(MyString& s) {
    if (s.empty()) {
        (void)s.begin();
        (void)s.end();
        (void)s.cbegin();
        (void)s.cend();
        (void)s.rbegin();
        (void)s.rend();
        (void)s.rcbegin();
        (void)s.rcend();
        return;
    }

    auto it = s.begin();
    const auto end = s.end();
    for (std::size_t n = 0; it != end && n < s.size(); ++it, ++n) {
        (void)*it;
        (void)it.operator->();
    }
    (void)(it == end);
    it = s.begin();
    (void)it++;

    auto cit = s.cbegin();
    const auto cend = s.cend();
    for (; cit != cend; ++cit) {
        (void)*cit;
        (void)cit.operator->();
    }
    (void)(cit == cend);
    cit = s.cbegin();
    (void)cit++;

    auto rit = s.rbegin();
    const auto rend = s.rend();
    for (std::size_t n = 0; rit != rend && n < s.size(); ++rit, ++n) {
        (void)*rit;
        (void)rit.operator->();
    }
    (void)(rit == rend);
    (void)(rit - rend);
    rit = s.rbegin();
    (void)rit++;

    auto crit = s.rcbegin();
    const auto crend = s.rcend();
    for (; crit != crend; ++crit) {
        (void)*crit;
        (void)crit.operator->();
    }
    (void)(crit == crend);
    crit = s.rcbegin();
    (void)crit++;

    if (s.size() > 1) {
        auto it_a = s.begin();
        auto it_b = it_a + 1;
        (void)(it_b - it_a);
        (void)(it_a - end);
        (void)(end - 1);
        it_a += 1;
        it_a -= 1;
        (void)(s.begin() - 0);
        (void)(1 + s.begin());
        (void)(s.cbegin() + 1);
        cit = s.cbegin();
        cit += 1;
        cit -= 1;
        (void)(1 + cit);
        (void)(cit - 1);
        (void)(s.rbegin() + 1);
        (void)(1 + s.rbegin());
        rit = s.rbegin();
        rit += 1;
        rit -= 1;
        (void)(rit - 1);
        (void)(s.rcbegin() + 1);
        (void)(1 + s.rcbegin());
        crit = s.rcbegin();
        crit += 1;
        crit -= 1;
        (void)(crit - 1);
        (void)(s.rcbegin() - s.rcend());
    }
}

void exercise_exception_paths(MyString& s) {
    try {
        MyString bad(static_cast<const char*>(nullptr));
        (void)bad;
    } catch (...) {
    }
    try {
        MyString bad(nullptr, 1);
        (void)bad;
    } catch (...) {
    }
    try {
        MyString bad("ab", 5);
        (void)bad;
    } catch (...) {
    }

    try {
        s = static_cast<const char*>(nullptr);
    } catch (...) {
    }
    s = s;

    try {
        s.append(static_cast<const char*>(nullptr));
    } catch (...) {
    }
    try {
        s.append(static_cast<const char*>(nullptr), 1);
    } catch (...) {
    }
    try {
        s.append(static_cast<const char*>(nullptr), 0, 1);
    } catch (...) {
    }
    try {
        s.append("ab", 5);
    } catch (...) {
    }
    try {
        s.append("ab", 3, 1);
    } catch (...) {
    }
    try {
        s.insert(0, static_cast<const char*>(nullptr));
    } catch (...) {
    }
    try {
        s.insert(0, static_cast<const char*>(nullptr), 1);
    } catch (...) {
    }
    try {
        s.insert(0, static_cast<const char*>(nullptr), 0, 1);
    } catch (...) {
    }
    try {
        s.replace(0, 0, static_cast<const char*>(nullptr));
    } catch (...) {
    }
    try {
        s.replace(0, 0, static_cast<const char*>(nullptr), 1);
    } catch (...) {
    }
    try {
        s.replace(0, 0, static_cast<const char*>(nullptr), 0, 1);
    } catch (...) {
    }
    try {
        s.append(-1, 'x');
    } catch (...) {
    }
    try {
        s.at(1'000'000);
    } catch (...) {
    }
    try {
        s.find_any({"x"}, 1'000'000);
    } catch (...) {
    }

    try {
        MyStringConversionError err("conversion failed");
        (void)err.what();
    } catch (...) {
    }

    try {
        MyString empty;
        (void)empty.to_int();
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }
    try {
        MyString sign_only("+");
        (void)sign_only.to_int();
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }
    try {
        MyString invalid_int("12x");
        (void)invalid_int.to_int();
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }
    try {
        MyString negative("-42");
        (void)negative.to_int();
    } catch (...) {
    }

    try {
        MyString empty;
        (void)empty.to_float();
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }
    try {
        MyString invalid_float("not-a-float");
        (void)invalid_float.to_float();
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }

    try {
        MyString from_int(-123);
        (void)from_int;
    } catch (...) {
    }
    try {
        MyString from_zero(0);
        (void)from_zero;
    } catch (...) {
    }
    try {
        MyString from_nan(std::numeric_limits<double>::quiet_NaN());
        (void)from_nan;
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }
    try {
        MyString from_inf(std::numeric_limits<double>::infinity());
        (void)from_inf;
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }
    try {
        MyString from_double(3.14);
        (void)from_double;
    } catch (...) {
    }

    const std::string st = "xy";
    const MyString ms("z");
    try {
        MyString bad_ctor(st, 10);
        (void)bad_ctor;
    } catch (...) {
    }

    s = MyString("abcd");
    try {
        s.append(st, 10);
    } catch (...) {
    }
    try {
        s.append(ms, 10);
    } catch (...) {
    }
    try {
        s.append("ab", 0, 3);
    } catch (...) {
    }
    try {
        s.append(st, 0, 3);
    } catch (...) {
    }
    try {
        s.append(ms, 0, 3);
    } catch (...) {
    }

    try {
        s.insert(0, "ab", 5);
    } catch (...) {
    }
    try {
        s.insert(0, st, 5);
    } catch (...) {
    }
    try {
        s.insert(0, ms, 5);
    } catch (...) {
    }
    try {
        s.insert(0, "ab", 0, 3);
    } catch (...) {
    }
    try {
        s.insert(0, st, 0, 3);
    } catch (...) {
    }
    try {
        s.insert(0, ms, 0, 3);
    } catch (...) {
    }

    try {
        s.replace(0, 1, "ab", 5);
    } catch (...) {
    }
    try {
        s.replace(0, 1, st, 5);
    } catch (...) {
    }
    try {
        s.replace(0, 1, ms, 5);
    } catch (...) {
    }
    try {
        s.replace(0, 1, "ab", 0, 3);
    } catch (...) {
    }
    try {
        s.replace(0, 1, st, 0, 3);
    } catch (...) {
    }
    try {
        s.replace(0, 1, ms, 0, 3);
    } catch (...) {
    }
    try {
        s.replace(0, 100, "x");
    } catch (...) {
    }

    try {
        MyString nan_str("nan");
        (void)nan_str.to_float();
    } catch (const MyStringConversionError& e) {
        (void)e.what();
    } catch (...) {
    }
}

void exercise_shrink_and_replace(MyString& s) {
    s = MyString(8, 'x');
    s.erase(0, 3);
    s.shrink_to_fit();

    s = MyString("ab");
    s.shrink_to_fit();

    s.clear();
    s.shrink_to_fit();

    s = MyString("hello world");
    s.replace(6, 5, s.c_str(), 6, 5);

    s = MyString("abcdef");
    s.replace(1, 2, "XYZ");
    s.replace(0, 0, "");
}

void exercise_move_and_io(MyString& s) {
    s = MyString("move");
    MyString donor("donor");
    s = std::move(donor);
    {
        MyString& self = s;
        s = std::move(self);
    }

    const char* path = "/tmp/mystring_fuzz_empty.tmp";
    {
        std::ofstream out(path, std::ios::trunc);
    }
    MyString from_file;
    {
        std::ifstream in(path);
        if (in) {
            in >> from_file;
        }
    }
    std::remove(path);
}

void exercise_full_coverage(MyString& s) {
    if (s.size() < 4) {
        s = MyString("abcd");
    }

    exercise_iterators(s);
    exercise_exception_paths(s);
    exercise_shrink_and_replace(s);
    exercise_move_and_io(s);

    if (!s.empty()) {
        try {
            auto bad_it = s.begin();
            bad_it -= 100;
            s.insert(bad_it, 'x');
        } catch (...) {
        }
        try {
            auto bad_cit = s.cbegin();
            bad_cit -= 100;
            (void)s.find("a", bad_cit);
        } catch (...) {
        }
    }

    const std::string tmp = "xy";
    const MyString ms("z");
    auto pos = s.begin();
    if (!s.empty()) {
        try {
            s.insert(pos, 1, '!');
            s.insert(pos, tmp.c_str());
            s.insert(pos, tmp);
            s.insert(pos, ms);
            s.insert(pos, tmp.c_str(), 1);
            s.insert(pos, tmp, 1);
            s.insert(pos, ms, 1);
            s.insert(pos, tmp.c_str(), 0, 1);
            s.insert(pos, tmp, 0, 1);
            s.insert(pos, ms, 0, 1);

            s.replace(pos, 0, tmp.c_str());
            s.replace(pos, 0, tmp);
            s.replace(pos, 0, ms);
            s.replace(pos, 0, tmp.c_str(), 1);
            s.replace(pos, 0, tmp, 1);
            s.replace(pos, 0, ms, 1);
            s.replace(pos, 0, tmp.c_str(), 0, 1);
            s.replace(pos, 0, tmp, 0, 1);
            s.replace(pos, 0, ms, 0, 1);

            s.erase(pos);
            if (s.size() > 1) {
                s.erase(s.begin(), s.end());
            }
        } catch (...) {
        }
    }

    if (!s.empty()) {
        try {
            (void)s.substr(s.cbegin());
            (void)s.substr(s.cbegin(), 1);
            (void)s.substr(s.cbegin(), s.cend());
            (void)s.find("a", s.cbegin());
            (void)s.find(tmp, s.cbegin());
            (void)s.find(ms, s.cbegin());
        } catch (...) {
        }
    }

    try {
        (void)s.find_any(std::initializer_list<const char*>{});
    } catch (...) {
    }
}

void exercise_find_any(MyString& s, Reader& r) {
    std::string tmp;
    std::uint8_t b0 = 0;

    if (r.read_cstr(tmp)) {
        try {
            (void)s.find_any({tmp.c_str(), "ab", "xyz"}, 0);
            (void)s.find_any({tmp, std::string("cd")}, 0);
            (void)s.find_any({make_from_cstr(tmp), MyString("ef")}, 0);
        } catch (...) {
        }
    }

    if (r.read_u8(b0) && !s.empty()) {
        try {
            (void)s.find_any({"a", "b"}, static_cast<int>(b0 % s.size()));
        } catch (...) {
        }
    }
}

void exercise_conversions(MyString& s, Reader& r) {
    std::uint8_t b0 = 0;

    if (r.read_u8(b0)) {
        try {
            MyString num(static_cast<int>(b0));
            (void)num.to_int();
        } catch (...) {
        }
        try {
            MyString num(static_cast<double>(b0) / 10.0);
            (void)num.to_float();
        } catch (...) {
        }
    }

    if (!s.empty()) {
        try {
            (void)s.to_int();
        } catch (...) {
        }
        try {
            (void)s.to_float();
        } catch (...) {
        }
    }
}

void exercise_file_io(MyString& s) {
    const char* path = "/tmp/mystring_fuzz_io.tmp";
    {
        std::ofstream out(path, std::ios::trunc);
        if (out) {
            out << s;
        }
    }
    MyString loaded;
    {
        std::ifstream in(path);
        if (in) {
            in >> loaded;
        }
    }
    if (!loaded.empty()) {
        s = loaded;
    }
    std::remove(path);
}

void dispatch(std::uint8_t op, MyString& s, Reader& r) {
    switch (op % 32) {
    case 0:
        exercise_constructors(s, r);
        break;
    case 1:
        exercise_assignment(s, r);
        break;
    case 2:
        exercise_core(s, r);
        break;
    case 3:
        exercise_append(s, r);
        break;
    case 4:
        exercise_insert_index(s, r);
        break;
    case 5:
        exercise_insert_iterator(s, r);
        break;
    case 6:
        exercise_erase(s, r);
        break;
    case 7:
        exercise_replace_index(s, r);
        break;
    case 8:
        exercise_replace_iterator(s, r);
        break;
    case 9:
        exercise_substr_find(s, r);
        break;
    case 10:
        exercise_compare_operators(s, r);
        break;
    case 11:
        exercise_accessors(s, r);
        break;
    case 12:
        exercise_iterators(s);
        break;
    case 13:
        exercise_find_any(s, r);
        break;
    case 14:
        exercise_conversions(s, r);
        break;
    case 15:
        exercise_file_io(s);
        break;
    case 16:
        exercise_full_coverage(s);
        break;
    default:
        exercise_core(s, r);
        exercise_iterators(s);
        break;
    }
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        return 0;
    }

    const auto data = read_input_file(argv[1]);
    if (data.empty()) {
        MyString s;
        try {
            exercise_full_coverage(s);
        } catch (...) {
        }
        return 0;
    }

    MyString s;
    Reader reader{data.data(), data.size(), 0};

    for (std::size_t cmd = 0; cmd < kMaxCommands; ++cmd) {
        std::uint8_t op = 0;
        if (!reader.read_u8(op)) {
            break;
        }
        try {
            dispatch(op, s, reader);
            if (s.size() > kMaxStringSize) {
                s.clear();
            }
        } catch (const std::exception&) {
        } catch (...) {
        }
    }

    try {
        exercise_full_coverage(s);
    } catch (...) {
    }

    return 0;
}

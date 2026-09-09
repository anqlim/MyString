import unittest

import mystring


class CoreTest(unittest.TestCase):
    def test_default_constructor(self):
        s = mystring.MyString()
        self.assertEqual(str(s), "")
        self.assertEqual(s.size(), 0)
        self.assertTrue(s.empty())
        self.assertEqual(s.capacity(), 0)

    def test_constructor_from_str(self):
        s = mystring.MyString("Hello world!")
        self.assertEqual(str(s), "Hello world!")
        self.assertEqual(s.size(), 12)
        self.assertEqual(s.capacity(), 13)

    def test_constructor_with_count(self):
        s = mystring.MyString("hello", 4)
        self.assertEqual(str(s), "hell")

    def test_constructor_fill(self):
        s = mystring.MyString(5, "!")
        self.assertEqual(str(s), "!!!!!")

    def test_clear_and_shrink(self):
        s = mystring.MyString("Hello world!")
        s.clear()
        self.assertEqual(str(s), "")
        self.assertEqual(s.capacity(), 13)

        s.assign("Hello world!")
        s.erase(5, 6)
        self.assertEqual(str(s), "Hello!")
        s.shrink_to_fit()
        self.assertEqual(s.size(), 6)
        self.assertEqual(s.capacity(), 7)


class AssignmentTest(unittest.TestCase):
    def test_assign(self):
        s = mystring.MyString()
        s.assign("hello")
        self.assertEqual(str(s), "hello")

        s.assign("!")
        self.assertEqual(str(s), "!")


class AccessorsTest(unittest.TestCase):
    def test_indexing(self):
        s = mystring.MyString("hello")
        self.assertEqual(s[0], "h")
        s[0] = "H"
        self.assertEqual(str(s), "Hello")


class AppendTest(unittest.TestCase):
    def test_append(self):
        s = mystring.MyString("ab")
        s.append("cd")
        s.append(2, "!")
        s.append(mystring.MyString("XY"))
        s.append("hello", 2)
        s.append("world", 1, 3)
        self.assertEqual(str(s), "abcd!!XYheorl")


class InsertTest(unittest.TestCase):
    def test_insert(self):
        s = mystring.MyString("aaaaa")
        s.insert(0, 1, "!")
        self.assertEqual(str(s), "!aaaaa")

        s.insert(3, 2, "@")
        self.assertEqual(str(s), "!aa@@aaa")

        s = mystring.MyString("aaaaa")
        s.insert(1, "@@@@@", 2)
        self.assertEqual(str(s), "a@@aaaa")


class EraseReplaceTest(unittest.TestCase):
    def test_erase_and_replace(self):
        s = mystring.MyString("Hello world!")
        s.erase(5, 6)
        self.assertEqual(str(s), "Hello!")

        s.replace(0, 5, "Hi")
        self.assertEqual(str(s), "Hi!")

        s = mystring.MyString("abcdef")
        s.replace(2, 2, "ZZZ")
        self.assertEqual(str(s), "abZZZef")


class SubstrFindTest(unittest.TestCase):
    def test_substr_and_find(self):
        s = mystring.MyString("Hello world!")
        self.assertEqual(str(s.substr(6, 5)), "world")
        self.assertEqual(s.find("world"), 6)
        self.assertEqual(s.find("o", 5), 7)
        self.assertEqual(s.find("xyz"), -1)
        self.assertEqual(s.find(mystring.MyString("wor")), 6)


class CompareTest(unittest.TestCase):
    def test_compare_and_operators(self):
        a = mystring.MyString("abc")
        b = mystring.MyString("abd")
        c = mystring.MyString("abc")

        self.assertLess(a.compare(b), 0)
        self.assertTrue(a == c)
        self.assertTrue(a != b)
        self.assertEqual(str(a + "!"), "abc!")

        a += "!"
        self.assertEqual(str(a), "abc!")


class ExceptionsTest(unittest.TestCase):
    def test_out_of_range(self):
        s = mystring.MyString("abc")
        with self.assertRaises(IndexError):
            s.substr(10, 1)
        with self.assertRaises(IndexError):
            s.erase(0, 10)


if __name__ == "__main__":
    unittest.main()

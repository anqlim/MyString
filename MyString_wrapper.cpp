#include <pybind11/pybind11.h>

#include "mystring.h"

namespace py = pybind11;

PYBIND11_MODULE(mystring, m) {
    py::class_<MyString>(m, "MyString")
        .def(py::init<>())
        .def(py::init<const char*>())
        .def(py::init<const char*, int>())
        .def(py::init<const MyString&>())
        .def(py::init<const MyString&, int>())
        .def(py::init<int, char>())

        .def("clear", &MyString::clear)
        .def("shrink_to_fit", &MyString::shrink_to_fit)
        .def("c_str", &MyString::c_str)
        .def("size", &MyString::size)
        .def("capacity", &MyString::capacity)
        .def("empty", &MyString::empty)

        .def("assign", py::overload_cast<const char*>(&MyString::operator=),
             py::return_value_policy::reference_internal)
        .def("assign", py::overload_cast<const MyString&>(&MyString::operator=),
             py::return_value_policy::reference_internal)
        .def("assign", py::overload_cast<char>(&MyString::operator=),
             py::return_value_policy::reference_internal)

        .def("append", py::overload_cast<int, char>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", py::overload_cast<const char*>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", py::overload_cast<const MyString&>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", py::overload_cast<const char*, int>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", py::overload_cast<const MyString&, int>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", py::overload_cast<const char*, int, int>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", py::overload_cast<const MyString&, int, int>(&MyString::append),
             py::return_value_policy::reference_internal)

        .def("insert", py::overload_cast<int, int, char>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", py::overload_cast<int, const char*>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", py::overload_cast<int, const MyString&>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", py::overload_cast<int, const char*, int>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", py::overload_cast<int, const MyString&, int>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", py::overload_cast<int, const char*, int, int>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", py::overload_cast<int, const MyString&, int, int>(&MyString::insert),
             py::return_value_policy::reference_internal)

        .def("erase", py::overload_cast<int, int>(&MyString::erase),
             py::return_value_policy::reference_internal)

        .def("replace", py::overload_cast<int, int, const char*>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("replace", py::overload_cast<int, int, const MyString&>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("replace", py::overload_cast<int, int, const char*, int>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("replace", py::overload_cast<int, int, const MyString&, int>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("replace", py::overload_cast<int, int, const char*, int, int>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("replace", py::overload_cast<int, int, const MyString&, int, int>(&MyString::replace),
             py::return_value_policy::reference_internal)

        .def("substr", py::overload_cast<int>(&MyString::substr, py::const_))
        .def("substr", py::overload_cast<int, int>(&MyString::substr, py::const_))

        .def("compare", [](const MyString& self, const MyString& other) { return self.compare(other); })
        .def("compare", [](const MyString& self, const char* other) {
            return self.compare(MyString(other));
        })

        .def("find", py::overload_cast<const char*>(&MyString::find, py::const_))
        .def("find", py::overload_cast<const char*, int>(&MyString::find, py::const_))
        .def("find", py::overload_cast<const MyString&>(&MyString::find, py::const_))
        .def("find", py::overload_cast<const MyString&, int>(&MyString::find, py::const_))

        .def("__iadd__", py::overload_cast<const char*>(&MyString::operator+=),
             py::return_value_policy::reference_internal)
        .def("__iadd__", py::overload_cast<const MyString&>(&MyString::operator+=),
             py::return_value_policy::reference_internal)
        .def("__add__", [](const MyString& lhs, const char* rhs) { return lhs + rhs; })
        .def("__add__", [](const MyString& lhs, const MyString& rhs) { return lhs + rhs; })
        .def("__eq__", [](const MyString& lhs, const MyString& rhs) { return lhs == rhs; })
        .def("__eq__", [](const MyString& lhs, const char* rhs) { return lhs == MyString(rhs); })
        .def("__ne__", [](const MyString& lhs, const MyString& rhs) { return lhs != rhs; })
        .def("__ne__", [](const MyString& lhs, const char* rhs) { return lhs != MyString(rhs); })
        .def("__getitem__", [](const MyString& self, int index) { return self[index]; })
        .def("__setitem__", [](MyString& self, int index, char ch) { self[index] = ch; })

        .def("__str__", &MyString::c_str)
        .def("__len__", &MyString::size);
}

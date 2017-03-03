//
// Created by Borchers, Henry Samuel on 3/1/17.
//
//#include <boost/python.hpp>
//char const *greet() {
//    return "Hello";
//
//}
//
//

#include <iostream>
#include <boost/python/dict.hpp>
#include "metadata.h"

using namespace boost::python;

struct Metadata {
    Metadata(const std::string &filename) : filename(filename) {}

    dict iptc() {
        dict d;
        for (auto &i : read_iptc_metadata(this->filename)) {
            d[i.key] = make_tuple(i.data_type, i.value);
        }
        return d;
    };
    std::string filename;
};


#include <boost/python.hpp>


BOOST_PYTHON_MODULE (exiv2_wrapper) {

    class_<Metadata>("Metadata", init<std::string>())
            .def("iptc", &Metadata::iptc);
//            .def("foo", &Metadata::foo);
}
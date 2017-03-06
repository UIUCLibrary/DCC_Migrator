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

class Metadata {
    std::string filename;

public:
    Metadata(const std::string &filename) : filename(filename) {}

    dict iptc() {
        dict d;
        for (auto &i : read_iptc_metadata(this->filename)) {
            d[i.key] = make_tuple(i.data_type, i.value);
        }
        return d;
    };

    dict xmp() {
        dict d;
        std::cout <<"HERE!!!!" << std::endl;
        for (auto &i : read_xmp_metadata(this->filename)) {
            d[i.key] = make_tuple(i.data_type, i.value);
        }
        return d;

    }

    dict exif() {
        dict d;
        for (auto &i : read_exif_metadata(this->filename)) {
            d[i.key] = make_tuple(i.data_type, i.value);
        }
        return d;
    }
};


#include <boost/python.hpp>


BOOST_PYTHON_MODULE (exiv2_wrapper) {

    class_<Metadata>("Metadata", init<std::string>())
            .def("iptc", &Metadata::iptc)
            .def("exif", &Metadata::exif)
            .def("xmp", &Metadata::xmp);
//            .def("foo", &Metadata::foo);
}
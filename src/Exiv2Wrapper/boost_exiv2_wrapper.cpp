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
#include "reader.h"

using namespace boost::python;

class ImageMetadata {
    std::string filename;

public:
    ImageMetadata(const std::string &filename) : filename(filename) {}

    dict iptc() {
        dict d;
        auto md = read_iptc_metadata2(this->filename);

        for(auto const &entry: md){
            auto const &key = entry.first;
            auto const &data = entry.second;
            d[key] = make_tuple(data.data_type, data.value);
        }
        return d;
    };

    dict xmp() {
        dict d;

        auto md = read_xmp_metadata2(this->filename);
        for(auto const &entry: md){

            std::string const &key = entry.first;
            auto const &data = entry.second;
            d[key] = make_tuple(data.data_type, data.value);
        }
        return d;

    }

    dict exif() {
        dict d;
        auto md = read_exif_metadata2(this->filename);
        for(auto const &entry: md){
            auto const &key = entry.first;
            auto const &data = entry.second;
            d[key] = make_tuple(data.data_type, data.value);
        }

        return d;
    }
};


#include <boost/python.hpp>


BOOST_PYTHON_MODULE (pyExiv2) {

    class_<ImageMetadata>("ImageMetadata", init<std::string>())
            .def("iptc", &ImageMetadata::iptc)
            .def("exif", &ImageMetadata::exif)
            .def("xmp", &ImageMetadata::xmp);
//            .def("foo", &ImageMetadata::foo);
}
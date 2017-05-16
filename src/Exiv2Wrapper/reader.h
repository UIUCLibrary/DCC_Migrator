//
// Created by hborcher on 1/31/2017.
//

#ifndef HELLOEXIV2_DUMMY_H
#define HELLOEXIV2_DUMMY_H

#include <string>
#include <vector>
#include <map>

//#include "ImageMetadata.h"

struct metadata_chunk {
    const std::string key;
    const std::string data_type;
    const std::string value;
};

struct metadata_chunk2 {
    std::string data_type;
    std::string value;

    metadata_chunk2() {};
    metadata_chunk2(const metadata_chunk2 &m): data_type(m.data_type), value(m.value){};

    metadata_chunk2(std::string const &dtype, std::string const &dvalue) : data_type(dtype), value(dvalue) {};

};

const std::vector<metadata_chunk> read_iptc_metadata(const std::string &filename);

const std::map<const std::string, metadata_chunk2> read_iptc_metadata2(const std::string &filename);

const std::vector<metadata_chunk> read_exif_metadata(const std::string &filename);

const std::map<const std::string, metadata_chunk2> read_exif_metadata2(const std::string &filename);

const std::vector<metadata_chunk> read_xmp_metadata(const std::string &filename);

const std::map<const std::string, metadata_chunk2> read_xmp_metadata2(const std::string &filename);

#endif //HELLOEXIV2_DUMMY_H

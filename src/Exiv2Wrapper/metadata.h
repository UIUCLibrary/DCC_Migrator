//
// Created by hborcher on 1/31/2017.
//

#ifndef HELLOEXIV2_DUMMY_H
#define HELLOEXIV2_DUMMY_H

#include <string>
#include <vector>
struct metadata_chunk{
    const std::string key;
    const std::string data_type;
    const std::string value;
};

int read_data(const std::string &filename);
const std::vector<metadata_chunk> read_iptc_metadata(const std::string &filename);
#endif //HELLOEXIV2_DUMMY_H

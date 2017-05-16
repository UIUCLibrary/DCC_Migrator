//
// Created by Borchers, Henry Samuel on 3/10/17.
//

#ifndef DCC_MIGRATOR_METADATA_H
#define DCC_MIGRATOR_METADATA_H

#include <exiv2/exiv2.hpp>
#include <string>
#include "reader.h"

class ImageMetadata {
private:
    const std::string filename;
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::Image::AutoPtr image;
public:
    ImageMetadata(const std::string &filename);

    void setExifData(const std::string &key, const std::string &value, const std::string &type = "ascii");

    const std::map<const std::string, metadata_chunk2> getExif();

    void write();

    void setXMPData(const std::string &key, const std::string &value, const std::string &type = "ascii");

    const std::map<const std::string, metadata_chunk2> getXMP();
};


#endif //DCC_MIGRATOR_METADATA_H

//
// Created by hborcher on 1/31/2017.
//

#include "reader.h"
#include <exiv2/exiv2.hpp>
#include <cassert>

using namespace std;


const std::vector<metadata_chunk> read_iptc_metadata(const std::string &filename) {

    vector<metadata_chunk> metadata;
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        assert (image.get() != 0);
        image->readMetadata();
        Exiv2::IptcData &iptcData = image->iptcData();
        if (iptcData.empty()) {
            string error(filename);
            error += ": no IPTC data found in file";
            throw Exiv2::Error(1, error);
        }
        Exiv2::IptcData::iterator end = iptcData.end();

        for (Exiv2::IptcData::iterator md = iptcData.begin(); md != end; ++md) {

            metadata_chunk x = {md->key(), string(md->typeName()), string(md->value().toString().c_str())};
            metadata.push_back(x);
        }
    } catch (Exiv2::AnyError &e) {
////        TODO: handle errors:
        throw;
    }

    return metadata;
}

const map<const string, metadata_chunk2> read_iptc_metadata2(const string &filename) {
    map<const string, metadata_chunk2> iptc_metadata;
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        assert (image.get() != 0);
        image->readMetadata();
        Exiv2::IptcData &iptcData = image->iptcData();
        if (iptcData.empty()) {
            string error(filename);
            error += ": no IPTC data found in file";
            throw Exiv2::Error(1, error);
        }
        Exiv2::IptcData::iterator end = iptcData.end();
        for (Exiv2::IptcData::iterator md = iptcData.begin(); md != end; ++md) {
            iptc_metadata[md->key().c_str()] = metadata_chunk2(md->typeName(), md->value().toString());
        }

    } catch (Exiv2::AnyError &e) {

        throw;
    }


    return iptc_metadata;
}

const std::vector<metadata_chunk> read_exif_metadata(const std::string &filename) {

    vector<metadata_chunk> metadata;
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        assert (image.get() != 0);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) {
            string error(filename);
            error += ": no Exif data found in file";
            throw Exiv2::Error(1, error);
        }
        Exiv2::ExifData::iterator end = exifData.end();

        for (Exiv2::ExifData::iterator md = exifData.begin(); md != end; ++md) {

            metadata_chunk x = {md->key(), string(md->typeName()), string(md->value().toString().c_str())};
            metadata.push_back(x);
        }
    } catch (Exiv2::AnyError &e) {
////        TODO: handle errors:
        throw;
    }

    return metadata;
}
const map<const string, metadata_chunk2> read_exif_metadata2(const std::string &filename) {
    map<const string, metadata_chunk2> metadata;
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        assert (image.get() != 0);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) {
            string error(filename);
            error += ": no Exif data found in file";
            throw Exiv2::Error(1, error);
        }
        Exiv2::ExifData::iterator end = exifData.end();

        for (Exiv2::ExifData::iterator md = exifData.begin(); md != end; ++md) {

            metadata[md->key().c_str()] = metadata_chunk2(md->typeName(), md->value().toString());
        }
    } catch (Exiv2::AnyError &e) {
////        TODO: handle errors:
        throw;
    }

    return metadata;
}


const std::vector<metadata_chunk> read_xmp_metadata(const std::string &filename) {

    vector<metadata_chunk> metadata;
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        assert (image.get() != 0);
        image->readMetadata();
        Exiv2::XmpData &xmpData = image->xmpData();
        if (xmpData.empty()) {
            string error(filename);
            error += ": no XmpData data found in file";
            throw Exiv2::Error(1, error);
        }
        Exiv2::XmpData::iterator end = xmpData.end();

        for (auto md = xmpData.begin(); md != end; ++md) {

            metadata_chunk x = {md->key(), string(md->typeName()), string(md->value().toString().c_str())};
            metadata.push_back(x);
        }
    } catch (Exiv2::AnyError &e) {
////        TODO: handle errors:
        throw;
    }

    return metadata;
}

const map<const string, metadata_chunk2> read_xmp_metadata2(const std::string &filename) {

    std::map<const string, metadata_chunk2> metadata;
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        assert (image.get() != 0);
        image->readMetadata();
        Exiv2::XmpData &xmpData = image->xmpData();
        if (xmpData.empty()) {
            string error(filename);
            error += ": no XmpData data found in file";
            throw Exiv2::Error(1, error);
        }
        Exiv2::XmpData::iterator end = xmpData.end();

        for (auto md = xmpData.begin(); md != end; ++md) {
            metadata[md->key().c_str()] = metadata_chunk2(string(md->typeName()), md->value().toString());
        }
    } catch (Exiv2::AnyError &e) {
////        TODO: handle errors:
        throw;
    }

    return metadata;
}


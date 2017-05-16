//
// Created by Borchers, Henry Samuel on 3/10/17.
//

#include "ImageMetadata.h"
#include "cassert"

using namespace std;

ImageMetadata::ImageMetadata(const std::string &filename) : filename(filename) {
    image = Exiv2::ImageFactory::open(filename);
    assert(image.get() != 0);
    assert(image->good());
    image->readMetadata();
    xmpData = image->xmpData();
    exifData = image->exifData();
}

void ImageMetadata::setExifData(const std::string &key, const std::string &value, const std::string &type) {

    if (type != "ascii") {
        throw std::logic_error("Only ascii types supported so far");
    }
    try {
//        Exiv2::Value::AutoPtr v = Exiv2::Value::create(Exiv2::asciiString);

//        v->read(value);

        exifData[key] = value;
//        tag.setValue(value);
//        exifData.add(Exiv2::ExifKey(key), v.get());
//        cout << "set " << tag.key() << " to " << tag.value() << endl;

    } catch (Exiv2::AnyError &e) {
//        To something
        throw;
    }


}

void ImageMetadata::write() {
    image->setXmpData(xmpData);
    image->setExifData(exifData);
    try {

        image->writeMetadata();
    } catch (Exiv2::AnyError &e){
        std::cout << e.what() << std::endl;
        throw ;
    }

}

const std::map<const std::string, metadata_chunk2> ImageMetadata::getExif() {

    map<const string, metadata_chunk2> metadata;
//    image->readMetadata();

//    Exiv2::ExifData &current_data = image->exifData();
    if (exifData.empty()) {
        string error(filename);
        error += ": no Exif data found in file";
        throw Exiv2::Error(1, error);
    }
    Exiv2::ExifData::iterator end = exifData.end();

    for (Exiv2::ExifData::iterator md = exifData.begin(); md != end; ++md) {

        metadata[md->key().c_str()] = metadata_chunk2(md->typeName(), md->value().toString());
    }
    return metadata;
}

void ImageMetadata::setXMPData(const std::string &key, const std::string &value, const std::string &type) {
    if (type != "ascii") {
        throw std::logic_error("Only ascii types supported so far");
    }
    try {

        Exiv2::XmpData::iterator pos = xmpData.findKey(Exiv2::XmpKey(key));
        if(pos != xmpData.end()){
            xmpData.erase(pos);
        }
        Exiv2::Xmpdatum &tag = xmpData[key];
        tag.setValue(value);
        xmpData[key] = tag;


    } catch (Exiv2::AnyError &e) {
//        To something
        throw;
    }

}

const std::map<const std::string, metadata_chunk2> ImageMetadata::getXMP() {
    map<const string, metadata_chunk2> metadata;

    if (xmpData.empty()) {
        string error(filename);
        error += ": no XMP data found in file";
        throw Exiv2::Error(1, error);
    }
    Exiv2::XmpData::iterator end = xmpData.end();

    for (Exiv2::XmpData::iterator md = xmpData.begin(); md != end; ++md) {

        metadata[md->key().c_str()] = metadata_chunk2(md->typeName(), md->value().toString());
    }
    return metadata;
}

//
// Created by Borchers, Henry Samuel on 3/7/17.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Exiv2Wrapper.h"

#define TEST_IMAGE "data//00000003.tif"
#define TEST_IMAGE2 "data/00000003_editable.tif"



TEST_CASE("GO THROUGH ALL") {
    auto md = read_xmp_metadata2(TEST_IMAGE);
    for (auto &x : md) {
        std::cout << x.first << std::endl;
    }
    REQUIRE(true);
}
SCENARIO("XMP metadata is modified"){
    GIVEN ("a tiff file with XMP metadata") {
        ImageMetadata tiff_file(TEST_IMAGE2);

        WHEN("a replacement value for an existing field is provided") {
            static const char *const DC_SOURCE = "Xmp.dc.source";
            static const char *const DC_CREATOR = "Xmp.dc.creator";
            tiff_file.setXMPData(DC_SOURCE, "test");
            tiff_file.setXMPData(DC_CREATOR, "test_creator");
            tiff_file.write();

            auto md = tiff_file.getXMP();
            REQUIRE(md[DC_SOURCE].value == "test");
            REQUIRE(md[DC_CREATOR].value == "test_creator");
        }
    }
}
SCENARIO("XMP metadata can be extracted") {
    GIVEN ("A tiff file with XMP metadata") {
        auto md = read_xmp_metadata2(TEST_IMAGE);

        WHEN("asked for Xmp.dc.title metadata ") {
            metadata_chunk2 mc = md[std::string("Xmp.dc.title")];

            THEN("the value should be lang=\"x-default\" RBML Digital Manuscript Collection") {
                REQUIRE(mc.value == "lang=\"x-default\" RBML Digital Manuscript Collection");
            }

            THEN("the type of value should be a LangAlt") {
                REQUIRE(mc.data_type == "LangAlt");
            }

        }

        WHEN("asked for Xmp.creator metadata ") {
            metadata_chunk2 mc = md[std::string("Xmp.dc.creator")];
            THEN("the value should be University of Illinois Library") {
                REQUIRE(mc.value == "University of Illinois Library");
            }

            THEN("the type of value should be a XmpSeq") {
                REQUIRE(mc.data_type == "XmpSeq");
            }
        }
        WHEN("asked for Xmp.iptc.CreatorContactInfo/Iptc4xmpCore:CiAdrExtadr metadata ") {
            metadata_chunk2 mc = md[std::string("Xmp.iptc.CreatorContactInfo/Iptc4xmpCore:CiAdrExtadr")];
            THEN("the value should be 1408 W. Gregory Drive") {
                REQUIRE(mc.value == "1408 W. Gregory Drive");
            }

            THEN("the type of value should be a String") {
                REQUIRE(mc.data_type == "XmpText");
            }
        }
    }

}

SCENARIO("EXIF data is modified") {
    GIVEN("a file tiff with with existing EXif data") {
        ImageMetadata tiff_file(TEST_IMAGE2);

        WHEN("is given replacement value for an existing field") {
            static const char *const MODEL = "Exif.Image.Model";

            tiff_file.setExifData(MODEL, "test model!");
            tiff_file.write();

            auto md = tiff_file.getExif();
            auto node = md[MODEL];
            REQUIRE(md[MODEL].value == "test model!");
        }
    }
}
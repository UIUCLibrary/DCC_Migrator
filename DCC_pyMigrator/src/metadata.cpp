//
// Created by hborcher on 1/31/2017.
//

#include "metadata.h"
#include <exiv2/exiv2.hpp>
#include <cassert>

int read_data(const std::string &filename) {
    using namespace std;
    cout << "using " << filename << endl;

    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        assert (image.get() != 0);
        image->readMetadata();
        Exiv2::IptcData &iptcData = image->iptcData();
        if(iptcData.empty()){
            string error(filename);
            error += ": no IPTC data found in file";
            throw Exiv2::Error(1, error);
        }
        Exiv2::IptcData::iterator end = iptcData.end();

        for(Exiv2::IptcData::iterator md = iptcData.begin(); md != end; ++md){
            cout << md->key() << ": " << md->typeName() << ": " << md->value() << endl;
        }


    } catch (Exiv2::AnyError& e){
        std::cerr << "caught exiv2 exception " << e << std::endl;
        return -1;
    }

    return 0;
}

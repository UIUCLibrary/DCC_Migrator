#include "convert.h"

#include <iostream>
#include <Magick++.h>

using namespace std;

enum class FileDirection {
    INPUT,
    OUTPUT
};


static string error_string;

static bool supported_format(const string &filename, FileDirection direction);

int convert(const char *input_name, const char *output_name) {
    using namespace Magick;

    if (!supported_format(input_name, FileDirection::INPUT)) {
        return 1;
    }

    if (!supported_format(output_name, FileDirection::OUTPUT)) {
        return 1;
    }

    Image image;
    try {
        image.read(input_name);
        image.write(output_name);
    } catch (Exception &error_) {
//        cerr << "exception: " << error_.what() << endl;
        error_string = error_.what();
        return 1;
    }
    return 0;
}

bool supported_format(const string &filename, FileDirection direction) {

    try {
        Magick::CoderInfo info(filename.substr(filename.find_last_of(".") + 1));

        if (direction == FileDirection::INPUT) {
            if (info.isReadable()) {
                return true;
            }
        } else if (direction == FileDirection::OUTPUT) {
            if (info.isWritable()) {
                return true;
            }
        }
        return false;

    } catch (Magick::Exception &error_) {
        error_string = error_.what();
        return false;
    }
}

int init_library(char *argv) {
    Magick::InitializeMagick(argv);
    return 0;
}

const char *get_error_str() {
    return error_string.c_str();
}

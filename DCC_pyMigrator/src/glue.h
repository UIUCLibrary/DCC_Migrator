#ifndef MAGICKWRAPPER_LIBRARY_H
#define MAGICKWRAPPER_LIBRARY_H
extern "C"{

int init_library(char *argv);
int convert(const char *input_name, const char *output_name);
const char *get_error_str();
};
#endif
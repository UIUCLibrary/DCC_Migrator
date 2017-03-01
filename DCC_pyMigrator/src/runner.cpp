//
// Created by Borchers, Henry Samuel on 3/1/17.
//
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "metadata.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "needs a file name");
        return EXIT_FAILURE;
    }

    const vector<metadata_chunk> &metadata = read_metadata(argv[1]);
    for (auto &i : metadata) {
        cout << "key : " << setw(40) << i.key << "| Type: " << setw(8) << i.data_type <<" | Value : " << i.value << endl;

    }
    return EXIT_SUCCESS;
}
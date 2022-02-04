

#include <cstdio>
#include <string>
#include <filesystem>
#include <algorithm>

#include "fmc/FCModel.h"

namespace fs = std::filesystem;

#include <chrono>
using namespace std::chrono;

/**
 * finlang executable.
 * given a directory with various models representing language and a text file
 * returns which language model better represents the text file.
 * Usage:
 *      findlang <model_dir> <text_file>
 */
int main (int argc, char *argv[]) {

    std::string exe_cmd = "findlang <model_dir> <text_file>\n";

    if (argc != 3) {
        printf("Wrong number of args|\n");
        printf("%s", exe_cmd.c_str());
        return 1;
    }

    printf("findlang: Comp\n");
    printf("cwd: %s\n", std::filesystem::current_path().c_str());
    printf("-----------------------\n");

    std::string model_dir = argv[1];
    std::string file_path = argv[2];

    FCModel m;

    std::vector<use_model_return> values;
    auto start = high_resolution_clock::now();

    for (const auto & entry : fs::directory_iterator(model_dir)) {
        if (!entry.is_directory()) {
            //load model
            auto ret_value = m.use_model(entry.path(), file_path);
            values.push_back(ret_value);
            printf("Using model (%s) on file (%s):\nLang: %s; NBits: %d\n", model_dir.c_str(), file_path.c_str(), ret_value.lang.c_str(), ret_value.num_bits);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printf("Full Duration: %d\n", duration.count());


    // sort results as to get the language with the least num of bits

    std::sort(values.begin(), values.end());
    auto result = values[0];

    printf("THe file seems to belong to language: %s (Num Bits: %d)\n", result.lang.c_str(), result.num_bits);

    return 0;
}

//
// Created by jfngsea on 24/01/22.
//

#include <cstdio>
#include <filesystem>
#include "string"

#include "fmc/FCModel.h"

/**
 * lang executable.
 * given a path for a model representative of a language and a text file
 * returns the number of bits necessary to represent that text file in the model's language.
 * Usage:
 *      lang <model_path> <text_file>
 */
int main (int argc, char *argv[]) {

    std::string exe_cmd = "lang <language_model> <text_file>\n";

    if (argc != 3) {
        printf("Wrong number of args|\n");
        printf("%s", exe_cmd.c_str());
        return 1;
    }

    printf("lang: Comp\n");
    printf("cwd: %s\n", std::filesystem::current_path().c_str());
    printf("-----------------------\n");

    std::string model_file = argv[1];
    std::string file = argv[2];

    auto ret_value = FCModel::use_model(model_file, file);

    printf("Using model (%s) on file (%s):\nNBits: %d\n", model_file.c_str(), file.c_str(), ret_value.num_bits);

    return 0;
}
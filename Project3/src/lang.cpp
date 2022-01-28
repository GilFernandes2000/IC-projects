//
// Created by jfngsea on 24/01/22.
//

#include <cstdio>
#include <filesystem>
#include "string"

#include "fmc/FCModel.h"

float get_value(FCModel m, std::string c ) {
    auto ctx = m.get_context();
    m.update_context(c);
    return m.get_value(ctx, c);
}

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

    auto n_bits = FCModel::use_model(model_file, file);

    printf("Using model (%s) on file (%s):\nNBits: %d\n", model_file.c_str(), file.c_str(), n_bits);

    return 0;
}
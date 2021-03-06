//
// Created by jfngsea on 16/01/22.
//

#include "stdio.h"
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

#include "fmc/FCModelFactory.h"

/**
 * fcm executable.
 * allows the training of model.
 * Usage:
 *      fcm <language> <model_order> <smoothing>
 */
int main (int argc, char *argv[]) {

    if (argc !=4) {
        printf("Wrong number of arguments! (fcm <lang> <model_order> <smoothing>)\n");
        return 1;
    }

    std::string lang = argv[1];
    int order, smoothing;

    try {
        order = std::stoi(argv[2]);
        smoothing = std::stoi(argv[3]);
    } catch (std::exception const &e) {
        printf("Wrong format of inputs!!\nExiting.......\n");
        return 2;
    }

    printf("fcm: train fc models\n");
    printf("cwd: %s\n", std::filesystem::current_path().c_str());
    printf("-----------------------\n");

    FCModelFactory f(lang, order, smoothing);

    while(true){
        char op = 0;
        std::string file_path;
        printf("Options:\n"
               " f <file_path>: process file\n"
               " d <dir_path>: process files in a directory\n"
               " s <file_path>: save counters to file\n"
               " l <file_path>: load counters from file\n"
               " m <file_path>: creates and outputs the probabilites model\n"
               " e <file_path>: load probabilities model and get entropy\n"
               " x: exit\n");
        std::cin >> op;
        if(op=='x'){return 0;}
        std::cin >> file_path;

        switch (op) {
            case 'd':

                for (const auto & entry : fs::directory_iterator(file_path))
                    if (!entry.is_directory()) {
                        f.readFile(entry.path());
                    }
                break;
            case 'f':
                f.readFile(file_path);
                break;

            case 's':
                f.save_to_file(file_path);
                break;

            case 'l':
                f.load_from_file(file_path);
                break;

            case 'm':
                // keeps scoping or throws error due to var init
                {
                    auto m = f.createModel();
                    m.save_to_file(file_path);
                    printf("\nEntropy: %f\n\n", m.getEntropy());
                }
                break;
            case 'e':
                // keeps scoping or throws error due to var init
            {
                auto m = f.createModel();
                m.save_to_file(file_path);
                printf("\nEntropy: %f\n\n", m.getEntropy());
            }
                break;
        }
    }

}

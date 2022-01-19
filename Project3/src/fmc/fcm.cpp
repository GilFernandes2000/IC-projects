//
// Created by jfngsea on 16/01/22.
//

#include "stdio.h"
#include <string>
#include <iostream>
#include "filesystem"
#include "FCModelFactory.h"

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
        printf("Options:\n f <file_path>: process file\n s <file_path>: save model to file\n l <file_path>: load model from file\n x: exit\n");
        std::cin >> op;
        std::cin >> file_path;

        switch (op) {

            case 'f':
                f.readFile(file_path);
                break;

            case 's':
                f.save_to_file(file_path);
                break;

            case 'l':
                f = FCModelFactory::load_from_file(file_path);
                break;

            case 'x':
                return 0;
        }
    }

}
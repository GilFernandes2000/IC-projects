//
// Created by joao- on 22/11/2021.
//
#include <iostream>
#include "../include/BitStream.h"
#include "../include/Golomb.h"


int main(){
    Golomb go(6, 17);
    string encode = go.enconding();
    cout << encode <<endl;
    return EXIT_SUCCESS;
}


